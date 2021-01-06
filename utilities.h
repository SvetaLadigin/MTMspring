#ifndef UTILITIES_H
#define UTILITIES_H

#include "stdbool.h"
#include "new_map.h"
#include "list.h"

/**
* Utilities kit for the program
* Helps with implementation of other functions
*
* The following functions are available:
        isValidId       - Checks fot valid ID
        isValidName:    - Checks if the name is valid
        copyString:     - Copies a certain string
        copyIntPtr:     - Copies an integer to a MapKeyElement
        safeFree        - Free for a pointer
        compareIntPtr   - Compares two ints
        comparePairs    - Compares two pairs of integer
        copyPair        - Copies a pair of 2 integers
        moveElement     - Copies the data element for the purpose of moving its place

*/
/** Type of function for printing a map element */
typedef void(*printListElement)(ListElement, void *context);
/**
 * isValidId: Checks fot valid ID
 * @param id
 * @return
 * 1 if correct
 * 0 otherwise
 */
bool isValidId(int id);
/**
 * isValidName: Checks if the name is valid
 * @param name
 * @return
 * 1 if correct
 * 0 otherwise
 */
bool isValidName(const char *name);
/**
 * copyString: Copies a certain string
 * @param str
 * @return
 */
char *copyString(const char *str);
/**typedef for int pointer*/
typedef int *IntPtr;
/**
 * copyIntPtr: copies an integer to a MapKeyElement
 * @param keyId
 * @return
 * the copied pointer
 */
MapKeyElement copyIntPtr(IntPtr keyId);
/**
 * safeFree: free for a pointer
 * @param ptr
 */
void safeFree(void *ptr);
/**
 * compareIntPtr: compares two ints
 * @param id1
 * @param id2
 * @return
 * 1 if id1 > id2
 * 0 if id1=id2
 * -1 otherwise
 */
int compareIntPtr(IntPtr id1, IntPtr id2);
/** typedef for a pair of 2 integers*/
typedef struct int_pair_t {
    int one;
    int two;
} *IntPair;
/**
 * comparePairs: compares two pairs of integer
 * @param pair1
 * @param pair2
 * @return
 * 1 if pair1 > pair2
 * 0 if pair1=pair2
 * -1 otherwise
 */
int comparePairs(IntPair pair1, IntPair pair2);
/**
 * copyPair: copies a pair of 2 integers
 * @param pair
 * @return
 * the pair
 * NULL otherwise
 */
IntPair copyPair(IntPair pair);
/**
 * moveElement: copies the data element for the purpose of moving its place
 * @param element
 * @return
 * MapDataElement copies element
 * NULL otherwise
 */
MapDataElement moveElement(MapDataElement element);

/**
* judgeGetJudgeScoreForPlace: get a judges score for specific state index
 *@param
 * index fot the score table
* @return
 * the relevant score
*/
int getScoreForPlace(int i);

/**
* dumpList: debug method for printing the list
* @param map
* 	Target list to print.
*   The method the print a single element
*   Context to pass to the printing method
* @return
* 	The data elements or NULL on memory error
*/
void dumpList(List list, printMapElement printElement, void *context);

#endif //UTILITIES_H
