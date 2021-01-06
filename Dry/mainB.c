#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node_t {
 int x;
 struct node_t *next;
} *Node;
typedef enum {
 SUCCESS=0,
 MEMORY_ERROR,
 EMPTY_LIST,
 UNSORTED_LIST,
} ErrorCode;
int getListLength(Node list);
bool isListSorted(Node list);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut);

Node createNode(int x);
void freeList(Node listHead);
ErrorCode concatenateList(Node listSource, Node listOut);

Node createNode(int x) {
    Node new_node = malloc(sizeof(struct node_t));
    if(!new_node) {
        return NULL;
    }

    new_node->x = x;
    new_node->next = NULL;

    return new_node;
}

void freeList(Node listHead) {
    while(listHead) {
        Node next = listHead->next;
        free(listHead);
        listHead = next;
    }
}

ErrorCode concatenateList(Node listSource, Node listOut) {
    while (listSource) {
        Node new_node = createNode(listSource->x);
        if(!new_node) {
            return MEMORY_ERROR;
        }
        listOut->next = new_node;
        listOut = new_node;
        listSource = listSource->next;
    }

    return SUCCESS;
}

ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut) {
    if(!mergedOut){
        return MEMORY_ERROR;

    }

    if((!list1) || (!list2)) {
        return EMPTY_LIST;
    }
    if((!isListSorted(list1)) || (!isListSorted(list2))) {
        return UNSORTED_LIST;
    }

    Node merged_list;
    if(list1->x >= list2->x) {
        merged_list = createNode(list1->x);
        list1 = list1->next;
    } else {
        merged_list = createNode(list2->x);
        list2 = list2->next;
    }
    if(!merged_list) {
        return MEMORY_ERROR;
    }
    Node merged_list_current_node = merged_list;

    while(list1 && list2) {
        Node new_node = NULL;

        if(list1->x >= list2->x) {
            new_node = createNode(list1->x);
            list1 = list1->next;
        } else {
            new_node = createNode(list2->x);
            list2 = list2->next;
        }
        if(!new_node) {
            freeList(merged_list);
            return MEMORY_ERROR;
        }

        merged_list_current_node->next = new_node;
        merged_list_current_node = new_node;
    }

    // Copy the remaining nodes from list1 or list 2
    ErrorCode error;
    error = concatenateList(list1, merged_list_current_node);
    if(error != SUCCESS) {
        freeList(merged_list);
        return MEMORY_ERROR;
    }
    error = concatenateList(list2, merged_list_current_node);
    if(error != SUCCESS) {
        freeList(merged_list);
        return MEMORY_ERROR;
    }

    *mergedOut = merged_list;
    return SUCCESS;
}
