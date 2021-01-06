#include "judge.h"

#include <stdlib.h>

#include "utilities.h"

struct judge_t {
    int id;
    char *name;
    int results[JUDGE_RESULTS_COUNT];
};
/**
 * copyResults: copies the score results
 * @param sourceResults
 * @param outResults
 */
static void copyResults(const int *sourceResults, int *outResults)
{
    for(int i = 0; i < JUDGE_RESULTS_COUNT; ++i) {
        outResults[i] = sourceResults[i];
    }
}

Judge judgeCreate(int judgeId, const char *judgeName, int *judgeResults) {
    Judge new_judge = malloc(sizeof(struct judge_t));
    if(!new_judge) {
        return NULL;
    }

    new_judge->id = judgeId;

    new_judge->name = copyString(judgeName);
    if(!new_judge->name) {
        judgeDestroy(new_judge);
        return NULL;
    }

    copyResults(judgeResults, new_judge->results);

    return new_judge;
}

void judgeDestroy(Judge judge) {
    if(!judge) {
        return;
    }

    if(judge->name) {
        free(judge->name);
        judge->name = NULL;
    }

    free(judge);
}

Judge judgeCopy(Judge judgeToCopy) {
    return judgeCreate(judgeToCopy->id, judgeToCopy->name, judgeToCopy->results);
}

int judgeGetId(Judge judge) {
    return judge->id;
}

const char *judgeGetName(Judge judge) {
    return judge->name;
}

int *judgeGetResults(Judge judge) {
    return judge->results;
}
