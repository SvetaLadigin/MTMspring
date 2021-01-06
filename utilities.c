#include "utilities.h"

#include <stdlib.h>
#include <string.h>

bool isValidId(int id) {
    return id >= 0;
}

static bool isValidChar(char c) {
    return ((c >= 'a') && (c <= 'z')) || (c == ' ');
}

bool isValidName(const char *name) {
    for(int i = 0; i < strlen(name); ++i) {
        if(!isValidChar(name[i])) {
            return false;
        }
    }
    return true;
}

char *copyString(const char *str) {
    char *copy = malloc(strlen(str) + 1);
    if(!copy) {
        return NULL;
    }
    strcpy(copy, str);

    return copy;
}

MapKeyElement copyIntPtr(IntPtr intPtr) {
    IntPtr int_ptr_copy = malloc(sizeof(int));
    if(!int_ptr_copy) {
        return NULL;
    }
    *int_ptr_copy = *intPtr;

    return int_ptr_copy;
}

void safeFree(void *ptr) {
    if(ptr) {
        free(ptr);
    }
}

int compareIntPtr(IntPtr id1, IntPtr id2) {
    return (*id1) - (*id2);
}

int comparePairs(IntPair pair1, IntPair pair2) {
    if(pair1->one != pair2->one) {
        return pair1->one - pair2->two;
    }
    if(pair1->two != pair2->two) {
        return pair1->two - pair2->two;
    }

    return 0;
}

IntPair copyPair(IntPair pair) {
    IntPair pair_copy = (IntPair)malloc(sizeof(struct int_pair_t));
    pair_copy->one = pair->one;
    pair_copy->two = pair->two;

    return pair_copy;
}

MapDataElement moveElement(MapDataElement element) {
    return element;
}

void dumpList(List list, printMapElement printElement, void *context) {
    LIST_FOREACH(ListElement, element, list) {
        printElement(element, context);
    }
}

int getScoreForPlace(int i) {
    if(i < 3) {
        return 12 - i * 2;
    }
    return 10 - i;
}
