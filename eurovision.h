#ifndef EUROVISION_H_
#define EUROVISION_H_

#include "list.h"
/**
* Eurovision program
*Runs the contest and gets the audience favorite and friendly states
*
* The following functions are available:
*eurovisionCreate                   - Creates a clear eurovision
eurovisionDestroy                   - Destroys the eurovision
 eurovisionAddState                 - Adds a new state to the contest
 eurovisionRemoveState              - Removes state from the contest
 eurovisionAddJudge                 - Adds a judge to the eurovision
 eurovisionRemoveJudge              - Removes judge from the contest
 eurovisionAddVote                  - Adds a vote to the system
 eurovisionRemoveVote               - Removesa vote to the system
 eurovisionRunContest               - Runs the eurovision contest and returns winners
 eurovisionRunAudienceFavorite      - Returns the top ten winners by the audiance votes
 eurovisionRunGetFriendlyStates     - Checks the states which gave each other 12 points

*/
/*typedef for the eurovision results*/
typedef enum eurovisionResult_t {
    EUROVISION_NULL_ARGUMENT,
    EUROVISION_OUT_OF_MEMORY,
    EUROVISION_INVALID_ID,
    EUROVISION_INVALID_NAME,
    EUROVISION_STATE_ALREADY_EXIST,
    EUROVISION_STATE_NOT_EXIST,
    EUROVISION_JUDGE_ALREADY_EXIST,
    EUROVISION_JUDGE_NOT_EXIST,
    EUROVISION_SAME_STATE,
    EUROVISION_SUCCESS
} EurovisionResult;
/**typedef for eurovision struct*/
typedef struct eurovision_t *Eurovision;
/**
* eurovisionCreate: Creates a clear eurovision
* @return
 * NULL if error.
 * eurovision if success.
*/
Eurovision eurovisionCreate();
/**
* eurovisionDestroy: destroys the eurovision
 *@param
 * eurovision
*/
void eurovisionDestroy(Eurovision eurovision);
/**
* eurovisionAddState: adds a new state to the contest
 *@param
 * eurovision - a eurovision to work on
 * stateId - unique ID for the state
 * Pointer to a state stateName and pointer to a state song name
* @return
 *    EUROVISION_NULL_ARGUMENT - if null was given
    EUROVISION_INVALID_ID - invaid ID (if not numbers)
    EUROVISION_INVALID_NAME - if name is not chars
    EUROVISION_STATE_ALREADY_EXIST - state already exists
    EUROVISION_SUCCESS - success! A new state was added to the contest
*/
EurovisionResult eurovisionAddState(Eurovision eurovision, int stateId,
                                    const char *stateName,
                                    const char *songName);
/**
* eurovisionRemoveState: removes state from the contest
 *@param
 * relevant eurovision and a stateID to remove
* @return
 *    EUROVISION_INVALID_ID - if contains chars
    EUROVISION_STATE_ALREADY_EXIST - if the name is not in the contest
*/
EurovisionResult eurovisionRemoveState(Eurovision eurovision, int stateId);
/**
* eurovisionAddJudge: Adds a judge to the eurovision
 *@param
 * relevant eurovision, judges ID, Judges name and the judges scores
* @return
    EUROVISION_INVALID_ID, - invalid id
    EUROVISION_INVALID_NAME - name contains special charecters
    EUROVISION_STATE_NOT_EXIST - state not exist
    EUROVISION_JUDGE_ALREADY_EXIST - the judge is already in the system
    EUROVISION_SUCCESS
*/
EurovisionResult eurovisionAddJudge(Eurovision eurovision, int judgeId,
                                    const char *judgeName,
                                    int *judgeResults);
/**
* eurovisionRemoveJudge: removes judge from the contest
 *@param
 * relevant eurovision and a judge's ID
* @return
 *     EUROVISION_INVALID_ID - invalid name
 *     EUROVISION_JUDGE_NOT_EXIST - invalid judge
 *
*/
EurovisionResult eurovisionRemoveJudge(Eurovision eurovision, int judgeId);
/**
* eurovisionAddVote: adds a vote to the system
 *@param
 *eurovision to add to, stateID of the voter and stateID to give the vote to
* @return
    EUROVISION_INVALID_ID, - invalid eurovision ID
    EUROVISION_STATE_NOT_EXIST, - state does not exist
    EUROVISION_SAME_STATE, - the voter wants to vote to his country
    EUROVISION_SUCCESS - success! vote added to the system
*/
EurovisionResult eurovisionAddVote(Eurovision eurovision, int stateGiver,
                                   int stateTaker);
/**
* eurovisionRemoveVote: removesa vote to the system
 *@param
 *eurovision to add to, stateID of the voter and stateID to give the vote to
* @return
    EUROVISION_INVALID_ID, - invalid eurovision ID
    EUROVISION_STATE_NOT_EXIST, - state does not exist
    EUROVISION_SAME_STATE, - the voter wants to remove vote to his country
    EUROVISION_SUCCESS - success! vote removed from the system
*/
EurovisionResult eurovisionRemoveVote(Eurovision eurovision, int stateGiver,
                                      int stateTaker);
/**
* eurovisionRunContest: runs the eurovision contest and returns winners
 *@param
 * relevant eurovision and the audiance precent
* @return
 * List of the top ten winner states of the eurovision
*/
List eurovisionRunContest(Eurovision eurovision, int audiencePercent);
/**
* eurovisionRunAudienceFavorite: returns the top ten winners by the audiance votes
 *@param
 * relevant eurovision
* @return
 * List of the top ten states which won the eurovision by the audience votes
*/
List eurovisionRunAudienceFavorite(Eurovision eurovision);
/**
* eurovisionRunGetFriendlyStates: checks the states which gave each other 12 points
 *@param
 * relevant eurovision
* @return
 * List of the friendly states in lecsycographical order
*/
List eurovisionRunGetFriendlyStates(Eurovision eurovision);


#endif /* EUROVISION_H_ */
