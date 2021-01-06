#include <stdlib.h>
#include "state.h"

struct state_t {
    int id;
    char *name;
    char *song;
    Map votes_value;
};
/**typed for the list filter*/
struct filter_context
{
    Map votes;
    int index;
};

/**
 * filterNotTopTenCountry: removes the countries not in the top ten places
 * @param element the list element
 * @param context the filter
 * @return
 * 1 if success
 * 0 otherwise
 */
static bool filterNotTopTenCountry(ListElement element, struct filter_context *context);

State stateCreate(int stateId, const char *stateName, const char *stateSong) {
    State new_state = malloc(sizeof(struct state_t));
    if(!new_state) {
        return NULL;
    }

    new_state->id = stateId;

    new_state->name = copyString(stateName);
    if(!new_state->name) {
        stateDestroy(new_state);
        return NULL;
    }

    new_state->song = copyString(stateSong);
    if(!new_state->song) {
        stateDestroy(new_state);
        return NULL;
    }
    Map new_map = mapCreate((copyMapDataElements) copyIntPtr, (copyMapDataElements) copyIntPtr,
                            (freeMapDataElements) safeFree, (freeMapKeyElements) safeFree,
                            (compareMapKeyElements) compareIntPtr);
    new_state->votes_value = new_map;
    return new_state;
}

void stateDestroy(State state) {
    if(!state) {
        return;
    }

    if(state->name) {
        free(state->name);
        state->name = NULL;
    }
    if(state->song) {
        free(state->song);
        state->song = NULL;
    }
    if(state->votes_value) {
        mapDestroy(state->votes_value);
    }

    state->id = 0;

    free(state);
}

State stateCopy(State stateToCopy) {
    State state_to_fill = stateCreate(stateToCopy->id, stateToCopy->name, stateToCopy->song);
    mapDestroy(state_to_fill->votes_value);
    state_to_fill->votes_value = mapCopy(stateToCopy->votes_value);
    return state_to_fill;
}

int stateGetId(State state) {
    return state->id;
}

const char *stateGetName(State state) {
    return state->name;
}

const char *stateGetSong(State state) {
    return state->song;
}

int stateVotesGetPerCountry(State votes, IntPtr ID){
    int* score = mapGet(votes->votes_value,ID);
    if(score == NULL)
        return 0;
    return *score;
}
StateResult stateAddVote(State votes, IntPtr ID_taker){
    if(!mapContains(votes->votes_value, ID_taker)) {
        int new_vote = 1;
        mapPut(votes->votes_value, ID_taker, &new_vote);
        return STATE_SUCCESS;
    }
    int *votes_for_country = mapGet(votes->votes_value, ID_taker);
    *votes_for_country += 1;

    return STATE_SUCCESS;
}

StateResult stateRemoveVote(State votes, IntPtr ID_taker){
    if(!mapContains(votes->votes_value, ID_taker)) {
        return STATE_VOTE_ITEM_DOES_NOT_EXIST;
    }

    int *votes_for_country = mapGet(votes->votes_value, ID_taker);
    if(*votes_for_country > 0) {
        *votes_for_country -= 1;
    }

    return STATE_SUCCESS;
}

void stateRemoveVotesForState(State state, IntPtr stateToRemove) {
    mapRemove(state->votes_value, stateToRemove);
}

static bool filterNotTopTenCountry(ListElement element, struct filter_context *context)
{
    context->index += 1;
    int *vote_count = mapGet(context->votes, element);
    if(!vote_count || *vote_count == 0) {
        return 0;
    }
    return context->index <= 10;
}

List stateTopTenVotedCountries(State state)
{
    if(state == NULL) {
        return NULL;
    }

    List sorted_list = mapConvertToSortedListByValue(state->votes_value, (CompareListElements) compareIntPtr);
    struct filter_context context = {state->votes_value, 0};
    List top_ten = listFilter(sorted_list, (FilterListElement)filterNotTopTenCountry, &context);
    listDestroy(sorted_list);
    return top_ten;
}

StateResult stateGetTopVotedState(State state, IntPtr topStateId)
{
    if(state == NULL || topStateId == NULL) {
        return STATE_NULL_ARGUMENT;
    }
    if(mapGetSize(state->votes_value) == 0) {
        *topStateId = 0;
        return STATE_VOTE_ITEM_DOES_NOT_EXIST;
    }
    int top_state = *(int*)mapGetFirst(state->votes_value);
    int maximum_vote_count = *(int *)mapGet(state->votes_value, &top_state);

    for(IntPtr state_id = (IntPtr) mapGetNext(state->votes_value); state_id; state_id = mapGetNext(state->votes_value))
    {
        int vote_count = *(int *)mapGet(state->votes_value, state_id);
        if(vote_count > maximum_vote_count) {
            maximum_vote_count = vote_count;
            top_state = *state_id;
        }
    }

    *topStateId = top_state;

    return STATE_SUCCESS;
}
