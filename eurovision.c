#include "eurovision.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "judge.h"
#include "state.h"
#include "string.h"

#define EPS (1e-6)

//#define PRINT_STUFF

struct eurovision_t {
    Map judges;
    Map states;
};

/**
* eurovisionGetState: Gets a state by a state ID from the contest
 *@param
 * relevant eurovision and a stateID
* @return
 * returns relevant state from the states map in the eurovision
 * NULL otherwise
*/
static State eurovisionGetState(Eurovision eurovision, int stateId);
/**
* eurovisionGetStateNameForId: Gets a state name by a state ID from the contest
 *@param
 * relevant eurovision and a stateID
* @return
 * returns relevant state name from the states map in the eurovision
 * NULL otherwise
*/
static const char *eurovisionGetStateNameForId(Eurovision eurovision, int stateId);
/**
* calculateJudgesScore: calculates the scores from the judges for a state
 *@param
 * relevant judge and the map of judges scores for a specific country
* @return
 * EUROVISION_OUT_OF_MEMORY if NULL argument was given
 * EUROVISION_SUCCESS otherwise
*/
static EurovisionResult calculateJudgesScore(Judge judge, Map stateJudgeScores);
/**
* calculateAudienceScore: calculates the scores from the audience for a state
 *@param
 * relevant state and the audience scores map for a specific country
* @return
 * EUROVISION_OUT_OF_MEMORY if NULL argument was given
 * EUROVISION_SUCCESS otherwise
*/
static EurovisionResult calculateAudienceScore(State current_state, Map stateAudienceScores);
/**
* calculateFinalScore: calculates the final score
 *@param
 * relevant judges score, audience score , relevant eurovision and the audience percent for the scores
* @return
 * the final score
 * NULL otherwise
*/
static double calculateFinalScore(Eurovision eurovision, int audiencePercent, double judgeScore, double audienceScore);
/**
* calculateStatesFinalScores: calculates the final scores for all the states
 *@param
 * relevant eurovision and the audience percent for the scores, map of the audience scores and judges score
* @return
 * List of the final scores
 * NULL otherwise
*/
static List calculateStatesFinalScores(Eurovision  eurovision, int audiencePercent,
                                       Map stateJudgeScores, Map stateAudienceScores);
/**
* getStatesAudienceScores: calculates the audience scores for the states
 *@param
 * relevant eurovision
* @return
 * Map of the final scores
 * NULL otherwise
*/
static Map getStatesAudienceScores(Eurovision eurovision);
/**
* getStatesJudgeScores: gets the judges scores for the states
 *@param
 * relevant eurovision
* @return
 * Map of the final scores
 * NULL otherwise
*/
static Map getStatesJudgeScores(Eurovision eurovision);
/**
* getWinnerStates: gets the winners of the contest
 *@param
 * relevant eurovision and list of the final scores
* @return
 * List of the top ten winners of the contest
 * NULL otherwise
*/
static List getWinnerStates(Eurovision eurovision, List stateFinalScores);

/** typedef for the state struct score*/
typedef struct state_score_t {
    double score;
    int state_id;
} *StateScore;
/**
* getOrCreateStateScore: gets a score for the country if there isn't creates the score in the map
 *@param
 * relevant Map of the stateScore and the stateID
* @return
 * stateScore element that holds the scores
 * NULL otherwise
*/
static StateScore getOrCreateStateScore(Map stateScoresMap, int stateId);
/**
* compareListScores: compares the scores from 2 lists
 *@param
 * 2 lists of scores to compare
* @return
 * 1 if same
 * -1 otherwise
*/
static int compareListScores(StateScore score1, StateScore score2);
/**
* copyScore: copies the score
 *@param
 * the relevant score
* @return
 * the score
 * NULL otherwise
*/
static MapKeyElement copyScore(StateScore score);

/**
* freeScore: frees score pointer
 *@param
 * the relevant score
*/
static void freeScore(StateScore score);

/**
* createFriendlyPair: Initialize the friendlyPair with the lower state id as the 1st and the higher as the 2nd
 *@param
 * the pair to initialize and the 2 state ids
*/
static void createFriendlyPair(IntPair friendlyPair, int stateId1, int stateId2);

// for debugging
#ifdef PRINT_STUFF
static void printScore(StateScore score, Eurovision eurovision) {
    printf("%d: %f - %s\n", score->state_id, score->score, eurovisionGetStateNameForId(eurovision, score->state_id));
}
#endif

Eurovision eurovisionCreate() {
    Eurovision eurovision = malloc(sizeof(struct eurovision_t));
    if(!eurovision) {
        return NULL;
    }

    // Since we create the judge and state objects internally we can just move instead of copying
    eurovision->judges = mapCreate((copyMapDataElements)judgeCopy, (copyMapKeyElements) copyIntPtr,
                                   (freeMapDataElements) judgeDestroy, (freeMapKeyElements) safeFree,
                                   (compareMapKeyElements) compareIntPtr);
    if(!eurovision->judges) {
        eurovisionDestroy(eurovision);
        return NULL;
    }

    eurovision->states = mapCreate((copyMapDataElements)stateCopy, (copyMapKeyElements) copyIntPtr,
                                   (freeMapKeyElements) stateDestroy, (freeMapKeyElements) safeFree,
                                   (compareMapKeyElements) compareIntPtr);
    if(!eurovision->states) {
        eurovisionDestroy(eurovision);
        return NULL;
    }

    return eurovision;
}

void eurovisionDestroy(Eurovision eurovision)
{
    if(!eurovision) {
        return;
    }
    if(eurovision->judges) {
        mapDestroy(eurovision->judges);
        eurovision->judges = NULL;
    }
    if(eurovision->states) {
        mapDestroy(eurovision->states);
        eurovision->states = NULL;
    }

    free(eurovision);
}

EurovisionResult eurovisionAddState(Eurovision eurovision, int stateId,
                                    const char *stateName,
                                    const char *songName) {
    if(!eurovision || !stateName || !songName) {
        return EUROVISION_NULL_ARGUMENT;
    }
    if(!isValidId(stateId)) {
        return EUROVISION_INVALID_ID;
    }
    if(!isValidName(stateName) || !isValidName(songName)) {
        return EUROVISION_INVALID_NAME;
    }
    if(mapContains(eurovision->states, &stateId)) {
        return EUROVISION_STATE_ALREADY_EXIST;
    }
    State new_state = stateCreate(stateId, stateName, songName);
    if(!new_state) {
        return EUROVISION_OUT_OF_MEMORY;
    }
    MapResult mapResult = mapPut(eurovision->states, &stateId, new_state);
    stateDestroy(new_state);
    if(mapResult == MAP_OUT_OF_MEMORY) {
        return EUROVISION_OUT_OF_MEMORY;
    }

    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionRemoveState(Eurovision eurovision, int stateIdToRemove) {
    if(!eurovision) {
        return EUROVISION_NULL_ARGUMENT;
    }
    if(!isValidId(stateIdToRemove)) {
        return EUROVISION_INVALID_ID;
    }

    MapResult mapResult = mapRemove(eurovision->states, &stateIdToRemove);
    if(mapResult == MAP_ITEM_DOES_NOT_EXIST) {
        return EUROVISION_STATE_NOT_EXIST;
    }

    Map tmp_judges_map = mapCopy(eurovision->judges);
    MAP_FOREACH(IntPtr, judge_id, tmp_judges_map) {
        Judge judge = mapGet(eurovision->judges, judge_id);
        if(!judge) {
            continue;
        }
        int *judge_results = judgeGetResults(judge);
        for(int i = 0; i < JUDGE_RESULTS_COUNT; ++i) {
            if(judge_results[i] == stateIdToRemove) {
                eurovisionRemoveJudge(eurovision, *judge_id);
                break;
            }
        }
    }
    mapDestroy(tmp_judges_map);

    MAP_FOREACH(IntPtr, state_id, eurovision->states) {
        State state = mapGet(eurovision->states, state_id);
        if(!state) {
            continue;
        }
        stateRemoveVotesForState(state, &stateIdToRemove);
    }

    return EUROVISION_SUCCESS;
}

static State eurovisionGetState(Eurovision eurovision, int stateId) {
    State state = mapGet(eurovision->states, &stateId);

    return state;
}

static const char *eurovisionGetStateNameForId(Eurovision eurovision, int stateId) {
    State state = eurovisionGetState(eurovision, stateId);
    if(!state) {
        return NULL;
    }
    return stateGetName(state);
}

static StateScore getOrCreateStateScore(Map scoresMap, int stateId) {
    if(!mapContains(scoresMap, &stateId)) {
        struct state_score_t new_score = {0, stateId};
        MapResult result = mapPut(scoresMap, &stateId, &new_score);
        if(result != MAP_SUCCESS) {
            return NULL;
        }
    }
    StateScore score = mapGet(scoresMap, &stateId);

    return score;
}

EurovisionResult eurovisionAddJudge(Eurovision eurovision, int judgeId,
                                    const char *judgeName,
                                    int *judgeResults) {
    if(!eurovision || !judgeName || !judgeResults) {
        return EUROVISION_NULL_ARGUMENT;
    }
    if(!isValidId(judgeId)) {
        return EUROVISION_INVALID_ID;
    }
    if(!isValidName(judgeName)) {
        return EUROVISION_INVALID_NAME;
    }
    for(int i = 0; i < JUDGE_RESULTS_COUNT; ++i) {
        if(!isValidId(judgeResults[i])) {
            return EUROVISION_INVALID_ID;
        }
        if(!mapContains(eurovision->states, &judgeResults[i])) {
            return EUROVISION_STATE_NOT_EXIST;
        }
    }

    if(mapContains(eurovision->judges, &judgeId)) {
        return EUROVISION_JUDGE_ALREADY_EXIST;
    }
    Judge new_judge = judgeCreate(judgeId, judgeName, judgeResults);
    if(!new_judge) {
        return EUROVISION_OUT_OF_MEMORY;
    }
    MapResult mapResult = mapPut(eurovision->judges, &judgeId, new_judge);
    judgeDestroy(new_judge);
    if(mapResult == MAP_OUT_OF_MEMORY) {
        return EUROVISION_OUT_OF_MEMORY;
    }

    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionRemoveJudge(Eurovision eurovision, int judgeId){
    if(!eurovision) {
        return EUROVISION_NULL_ARGUMENT;
    }

    if(!isValidId(judgeId)) {
        return EUROVISION_INVALID_ID;
    }

    MapResult mapResult = mapRemove(eurovision->judges, &judgeId);
    if(mapResult == MAP_ITEM_DOES_NOT_EXIST) {
        return EUROVISION_JUDGE_NOT_EXIST;
    }

    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionAddVote(Eurovision eurovision, int stateGiver,
                                   int stateTaker) {
    if(!eurovision) {
        return EUROVISION_NULL_ARGUMENT;
    }

    if(!isValidId(stateGiver) || !isValidId(stateTaker)) {
        return EUROVISION_INVALID_ID;
    }

    if(!mapContains(eurovision->states, &stateTaker)) {
        return EUROVISION_STATE_NOT_EXIST;
    }

    State giverState = eurovisionGetState(eurovision, stateGiver);
    if(!giverState) {
        return EUROVISION_STATE_NOT_EXIST;
    }

    if(stateGiver == stateTaker) {
        return EUROVISION_SAME_STATE;
    }

    if(STATE_OUT_OF_MEMORY == stateAddVote(giverState, &stateTaker)) {
        return EUROVISION_OUT_OF_MEMORY;
    }

    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionRemoveVote(Eurovision eurovision, int stateGiver,
                                      int stateTaker){
    if(!eurovision) {
        return EUROVISION_NULL_ARGUMENT;
    }

    if(!isValidId(stateGiver) || !isValidId(stateTaker)) {
        return EUROVISION_INVALID_ID;
    }
    if(!mapContains(eurovision->states, &stateTaker)) {
        return EUROVISION_STATE_NOT_EXIST;
    }

    State giverState = eurovisionGetState(eurovision, stateGiver);
    if(!giverState) {
        return EUROVISION_STATE_NOT_EXIST;
    }

    if(stateGiver == stateTaker) {
        return EUROVISION_SAME_STATE;
    }

    if(STATE_OUT_OF_MEMORY == stateRemoveVote(giverState, &stateTaker)) {
        return EUROVISION_OUT_OF_MEMORY;
    }

    return EUROVISION_SUCCESS;
}

List eurovisionRunContest(Eurovision eurovision, int audiencePercent) {
    if(!eurovision) {
        return NULL;
    }

    Map state_judges_scores = getStatesJudgeScores(eurovision);
    if(!state_judges_scores) {
        return NULL;
    }

    Map state_audience_scores = getStatesAudienceScores(eurovision);
    if(!state_audience_scores) {
        mapDestroy(state_judges_scores);
        return NULL;
    }

    List state_final_scores = calculateStatesFinalScores(eurovision, audiencePercent,
                                                        state_judges_scores, state_audience_scores);
    mapDestroy(state_audience_scores);
    mapDestroy(state_judges_scores);
    if(!state_final_scores) {
        return NULL;
    }

    List winners = getWinnerStates(eurovision, state_final_scores);
    listDestroy(state_final_scores);

    return winners;
}

List eurovisionRunAudienceFavorite(Eurovision eurovision){
    if(!eurovision) {
        return NULL;
    }

    Map state_audience_scores = getStatesAudienceScores(eurovision);
    if(!state_audience_scores) {
        return NULL;
    }
    List final_list = eurovisionRunContest(eurovision, 100);
    mapDestroy(state_audience_scores);

    return final_list;
}

static char* twoStatesToString(const char* str1, const char* str2){
    const char* dash = " - ";
    int buffer_size = strlen(str1) + strlen(str2) + strlen(dash) + 1;
    char* final_word = malloc(buffer_size);
    if(strcmp(str1, str2) > 0) {
        strcpy(final_word,str2);
        strcat(final_word,dash);
        strcat(final_word,str1);
    } else {
        strcpy(final_word,str1);
        strcat(final_word,dash);
        strcat(final_word,str2);
    }
    return final_word;

}

static void createFriendlyPair(IntPair friendlyPair, int stateId1, int stateId2) {
    if(stateId1 < stateId2) {
        friendlyPair->one = stateId1;
        friendlyPair->two = stateId2;
    } else {
        friendlyPair->one = stateId2;
        friendlyPair->two = stateId1;
    }
}

List eurovisionRunGetFriendlyStates(Eurovision eurovision)
{
    Map friendly_map = mapCreate((copyMapDataElements)copyIntPtr, (copyMapKeyElements)copyPair, safeFree, safeFree,
                                 (compareMapKeyElements)comparePairs);
    if(!friendly_map) {
        return NULL;
    }

    List results = listCreate((CopyListElement)moveElement,(FreeListElement)free);
    if(!results) {
        mapDestroy(friendly_map);
        return NULL;
    }

    MAP_FOREACH(IntPtr, state_id, eurovision->states) {
        State current_state = eurovisionGetState(eurovision, *state_id);
        if(!current_state) {
            continue;
        }

        int top_state;
        if(STATE_SUCCESS != stateGetTopVotedState(current_state, &top_state)) {
            continue;
        }

        struct int_pair_t friendly_pair;
        createFriendlyPair(&friendly_pair, top_state, *state_id);

        if(!mapContains(friendly_map, &friendly_pair)) {
            int one = 1;
            mapPut(friendly_map, &friendly_pair, &one);
        } else {
            int *pair_count = mapGet(friendly_map, &friendly_pair);
            *pair_count += 1;
        }
    }

    MAP_FOREACH(IntPair, friendly_pair, friendly_map) {
        int *pair_count = mapGet(friendly_map, friendly_pair);
        if(*pair_count != 2) {
            continue;
        }
        const char *first_state = eurovisionGetStateNameForId(eurovision, friendly_pair->one);
        const char *second_state = eurovisionGetStateNameForId(eurovision, friendly_pair->two);

        listInsertFirst(results, twoStatesToString(first_state, second_state));
    }
    mapDestroy(friendly_map);
    listSort(results, (CompareListElements)strcmp);

    return results;
}

static List getWinnerStates(Eurovision eurovision, List stateFinalScores) {
    List winners = listCreate((CopyListElement) copyString, free);
    LIST_FOREACH(StateScore, score, stateFinalScores) {
        const char *state_name = eurovisionGetStateNameForId(eurovision, score->state_id);
        listInsertFirst(winners, (ListElement)state_name);
    }
    return winners;
}

static Map getStatesJudgeScores(Eurovision eurovision) {
    Map state_judges_scores = mapCreate((copyMapDataElements) copyScore, (copyMapKeyElements) copyIntPtr,
                                        (freeMapDataElements) freeScore, (freeMapKeyElements) safeFree,
                                        (compareMapKeyElements) compareIntPtr);
    if(!state_judges_scores) {
        return NULL;
    }

    MAP_FOREACH(IntPtr, judge_id, eurovision->judges) {
        Judge judge = mapGet(eurovision->judges, judge_id);
        if(EUROVISION_SUCCESS != calculateJudgesScore(judge, state_judges_scores)) {
            mapDestroy(state_judges_scores);
            return NULL;
        }
    }
    return state_judges_scores;
}

static Map getStatesAudienceScores(Eurovision eurovision) {
    Map state_audience_scores = mapCreate((copyMapDataElements) copyScore, (copyMapKeyElements) copyIntPtr,
                                          (freeMapDataElements) freeScore, (freeMapKeyElements) safeFree,
                                          (compareMapKeyElements) compareIntPtr);
    if(!state_audience_scores) {
        return NULL;
    }

    MAP_FOREACH(IntPtr, state_id, eurovision->states) {
        State current_state = eurovisionGetState(eurovision, *state_id);
        if(!current_state) {
            continue;
        }
        if(EUROVISION_SUCCESS != calculateAudienceScore(current_state, state_audience_scores)) {
            mapDestroy(state_audience_scores);
            return NULL;
        }
    }

    return state_audience_scores;
}

static EurovisionResult calculateJudgesScore(Judge judge, Map stateJudgeScores) {
    int *judge_results = judgeGetResults(judge);
    for(int i = 0; i < JUDGE_RESULTS_COUNT; ++i) {
        StateScore score = getOrCreateStateScore(stateJudgeScores, judge_results[i]);
        if(!score) {
            return EUROVISION_OUT_OF_MEMORY;
        }
        score->score += getScoreForPlace(i);
    }

    return EUROVISION_SUCCESS;
}

static EurovisionResult calculateAudienceScore(State current_state, Map stateAudienceScores) {
    int i = 0;
    List top_ten_countries = stateTopTenVotedCountries(current_state);
    LIST_FOREACH(IntPtr, state_id, top_ten_countries) {
        StateScore score = getOrCreateStateScore(stateAudienceScores, *state_id);
        if(!score) {
            listDestroy(top_ten_countries);
            return EUROVISION_OUT_OF_MEMORY;
        }
        score->score += getScoreForPlace(i);
        ++i;
    }
    listDestroy(top_ten_countries);
    return EUROVISION_SUCCESS;
}

static List calculateStatesFinalScores(Eurovision  eurovision, int audiencePercent,
                                      Map stateJudgeScores, Map stateAudienceScores) {
    List state_final_scores = listCreate((CopyListElement)copyScore, (FreeListElement)freeScore);
    if(!state_final_scores) {
        return NULL;
    }

    MAP_FOREACH(IntPtr, state_id, eurovision->states) {
        double judge_score = 0;
        double votes_score = 0;
        if(mapContains(stateJudgeScores, state_id)) {
            StateScore judge_map_score = (StateScore)mapGet(stateJudgeScores, state_id);
            judge_score = judge_map_score->score;
        }
        if(mapContains(stateAudienceScores, state_id)) {
            StateScore votes_map_score = (StateScore)mapGet(stateAudienceScores, state_id);
            votes_score = votes_map_score->score;
        }
        struct state_score_t final_score = {calculateFinalScore(eurovision, audiencePercent, judge_score, votes_score), *state_id};
        listInsertLast(state_final_scores, (ListElement)&final_score);
    }

    listSort(state_final_scores, (CompareListElements)compareListScores);

    //for debugging
#ifdef PRINT_STUFF
    printf("There are %d judges\n", mapGetSize(eurovision->judges));
    printf("There are %d states\n", mapGetSize(eurovision->states));
    printf("stateJudgeScores\n");
    dumpMap(stateJudgeScores, (printMapElement)printScore, eurovision);
    printf("stateAudienceScores\n");
    dumpMap(stateAudienceScores, (printMapElement)printScore, eurovision);
    printf("state_final_scores\n");
    dumpList(state_final_scores, (printListElement)printScore, eurovision);
#endif
    return state_final_scores;
}

static double calculateFinalScore(Eurovision eurovision, int audiencePercent, double judgeScore, double audienceScore) {
    double final_judge_score = 0;
    if(mapGetSize(eurovision->judges) != 0) {
        final_judge_score = judgeScore / mapGetSize(eurovision->judges);
    }
    double final_audience_score = 0;
    if(mapGetSize(eurovision->states) > 1) {
        final_audience_score = audienceScore / (mapGetSize(eurovision->states) - 1);
    }
    return (final_judge_score * (100 - audiencePercent) + final_audience_score * audiencePercent) / 100;
}

static int compareListScores(StateScore score1, StateScore score2) {
    double result = score1->score - score2->score;
    if(fabs(result) < EPS)
        return score2->state_id - score1->state_id;
    if(result > 0)
        return 1;

    return -1;
}

static MapKeyElement copyScore(StateScore score) {
    StateScore score_copy = malloc(sizeof(struct state_score_t));
    if(!score_copy) {
        return NULL;
    }
    score_copy->score = score->score;
    score_copy->state_id = score->state_id;

    return score_copy;
}

static void freeScore(StateScore score) {
    if(score) {
        free(score);
    }
}

