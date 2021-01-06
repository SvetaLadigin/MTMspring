#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include "new_map.h"
#include "list.h"
#include "utilities.h"
/**
* State object
* Represents the state object in the contest, has ID, name and song.
*
* The following functions are available:
 stateCreate                - Creates a new state
 stateCopy                  - Copies a given state
 stateDestroy               - Destries a given state
 stateGetId                 - Get states ID
 stateGetName               - Get states name
 stateGetSong               - Return states song
 stateAddVote               - Adds a vote to a state
 stateVotesGetPerCountry    - Gets the relevant vote for the country
 stateRemoveVote            - Removes one vote for the state
 stateRemoveVotesForState   - Removes multiple votes for a state
 stateTopTenVotedCountries  - Returns the top ten countries by votes
*/
typedef enum StateResult_t {
    STATE_SUCCESS,
    STATE_OUT_OF_MEMORY,
    STATE_NULL_ARGUMENT,
    STATE_VOTE_ITEM_DOES_NOT_EXIST,
    STATE_VOTE_SAME_STATE
} StateResult;

/**
* state
 *@param
* @return
*/
typedef struct state_t *State;
/**
* stateCreate: creates a new state
 *@param
 * state Id, state Name,state Song
* @return
 *NULL if error
 * new state otherwise
*/
State stateCreate(int stateId, const char *stateName, const char *stateSong);
/**
* stateCopy: copies a given state
 *@param
 * relevant state to copy
* @return
 * NULL if error
 * new copied state otherwise
*/
State stateCopy(State stateToCopy);
/**
* stateDestroy: destries a given state
 *@param
 * relevant state to destroy
*/
void stateDestroy(State state);
/**
* stateGetId: get states ID
 *@param
 * relevant state
* @return
 * states ID
*/
int stateGetId(State state);
/**
* stateGetName: get states name
 *@param
 * releant state
* @return
 * states name
*/
const char *stateGetName(State state);
/**
* stateGetSong: return states song
 *@param
 * relevant state
* @return
 * states song
*/
const char *stateGetSong(State state);
/**
* stateAddVote: adds a vote to a state
 *@param
 * relevant state and ID of the state to give
* @return
 *
*/
StateResult stateAddVote(State votes, IntPtr ID_taker);
/**
 * stateVotesGetPerCountry: Gets the relevant vote for the country
 * @param votes relevant state
 * @param ID the pointer for the country ID
 * @return
 * the score
 * NULL otherwise
 */
int stateVotesGetPerCountry(State votes, IntPtr ID);
/**
 * stateRemoveVote: removes one vote for the state
 * @param votes the relevant state
 * @param ID_taker ID of the relevant state
 * @return
 * VOTE_ITEM_DOES_NOT_EXIST if the ID doesnt exist
 * VOTE_SUCCESS otherwise
 */
StateResult stateRemoveVote(State votes, IntPtr ID_taker);
/**
 * stateRemoveVotesForState: removes multiple votes for a state
 * @param state the state
 * @param stateToRemove state to remove
 */
void stateRemoveVotesForState(State state, IntPtr stateToRemove);
/**
 * topTenPerCountry: returns the top ten countries by votes
 * @param state the relevant state
 * @return
 * List of the top ten countries
 * NULL otherwise
 * */
List stateTopTenVotedCountries(State state);

/**
 * topTenPerCountry: returns the top state by votes
 * @param state the relevant state
 * @param topStateId out parameter for the top state
 * @return
 * STATE_NULL_ARGUMENT
 * STATE_VOTE_ITEM_DOES_NOT_EXIST nobody voted
 * STATE_SUCCESS otherwise
 * */
StateResult stateGetTopVotedState(State state, IntPtr topStateId);

#endif //STATE_H
