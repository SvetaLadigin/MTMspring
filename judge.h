#ifndef JUDGE_H
#define JUDGE_H

#define JUDGE_RESULTS_COUNT (10)

/**
* Judge object
* Represents the judges in the eurovision contest
* Has: name, ID and scores for the countries
*
* The following functions are available:
    judgeCreate                  - Creates a new judge in the system
    judgeDestroy                 - Destroys the judge
    judgeCopy                    - Copies a given judge
    judgeGetID                   - Returns the judges ID
    judgeGetName                 - Returns judges name
    judgeGetResults              - Returns the judges scores to the states
    judgeGetJudgeScoreForPlace   - Get a judges score for specific state index

*/

/**typedef for the judge struct*/
typedef struct judge_t *Judge;

/**
* judgeCreate: creates a new judge in the system
 *@param
 * judges name, ID and his scores to the states
* @return
 * NULL if the program couldnt allocate a new judge
 * a new judge if succeed
*/
Judge judgeCreate(int judgeId, const char *judgeName, int *judgeResults);
/**
* judgeDestroy: Destroys the judge
 *@param
 * relevant judge
*/
void judgeDestroy(Judge judge);
/**
* judgeCopy: copies a given judge
 *@param
 * relevant judge
* @return
 * NULL if error
 * new judge if succeed
*/
Judge judgeCopy(Judge judgeToCopy);
/**
* judgeGetID: returns the judges ID
 *@param
 * relevant judge
* @return
 * NULL if error
 * if succeeds the judges ID number
*/
int judgeGetId(Judge judge);
/**
* judgeGetName: returns judges name
 *@param
 * relevant judge
* @return
 * NULL if error
 * if succeeds the judges name
*/
const char *judgeGetName(Judge judge);
/**
* judgeGetResults: returns the judges scores to the states
 *@param
 * relevant judge
* @returnN
 * NULL if error
 * the judge's scores otherwise
*/
int *judgeGetResults(Judge judge);

#endif //JUDGE_H
