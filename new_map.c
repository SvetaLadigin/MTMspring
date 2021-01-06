

#include <stdbool.h>
#include<stdlib.h>
#include <stdio.h>
#include "new_map.h"


/** struct for node used in the map, creates a linked list node*/
typedef struct Node_t {
    MapKeyElement* key_element;
    MapDataElement* data_element;
    struct Node_t* next;

} *Node;

/**
 * CreateNode: Creates new node for the map
 * @param key the relevant key element
 * @param value the value
 * @return
 * new Node if success
 * NULL otherwise
 */
static  Node CreateNode(MapKeyElement key, MapDataElement value ){
    Node new_node = malloc(sizeof(struct Node_t));
    if(new_node == NULL)
        return NULL;
    new_node->key_element = key;
    new_node->data_element = value;
    new_node->next = NULL;
    return new_node;


}
/**
 * destroyNode: destroys map node
 * @param node relevant node to destroy
 */
static void destroyNode(Node node) {
    node->key_element=NULL;
    node->data_element=NULL;
    node->next=NULL;
    free(node);

}
struct Map_t  {
    copyMapDataElements copyDataElement;
    copyMapKeyElements copyKeyElement;
    freeMapDataElements freeDataElement;
    freeMapKeyElements freeKeyElement;
    compareMapKeyElements compareKeyElements;
    Node head;
    int size;
    Node map_it;

};

Map mapCreate(copyMapDataElements copyDataElement,
              copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement,
              freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements){
    if(copyKeyElement == NULL || copyDataElement == NULL || freeDataElement == NULL || freeKeyElement == NULL || compareKeyElements == NULL) {
        return NULL;
    }

    Map map = malloc(sizeof(struct Map_t));
    if(map == NULL){
        return NULL;
    }
    map->compareKeyElements = compareKeyElements;
    map->copyDataElement = copyDataElement;
    map->copyKeyElement = copyKeyElement;
    map->freeDataElement = freeDataElement;
    map->freeKeyElement = freeKeyElement;
    map->head = NULL;
    map->map_it = map->head;
    map->size = 0;
    return map;


}

void mapDestroy(Map map){
    if(map != NULL){
        Node iterator = map->head;
        while (iterator != NULL){
            Node current_node = iterator;
            iterator = current_node->next;
            map->freeKeyElement(current_node->key_element);
            map->freeDataElement(current_node->data_element);
            free(current_node);

        }
        free(map);
    }

}

Map mapCopy(Map map){
    Map new_map = mapCreate(map->copyDataElement, map->copyKeyElement, map->freeDataElement, map->freeKeyElement, map->compareKeyElements);
    if(new_map == NULL)
        return NULL;
    if(map->size > 0) {
        for (Node it = map->head; it; it = it->next) {
            mapPut(new_map, it->key_element, it->data_element);
        }
    }
    return new_map;
}

int mapGetSize(Map map){
    if(map==NULL)
        return -1;
    return map->size;
}

bool mapContains(Map map, MapKeyElement element){
    return mapGet(map, element) != NULL;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){

    if(map == NULL){
        return MAP_NULL_ARGUMENT;
    }

    MapKeyElement copy_key = map->copyKeyElement(keyElement);
    MapDataElement copy_data = map->copyDataElement(dataElement);

    if(copy_key==NULL || copy_data == NULL){
        return MAP_OUT_OF_MEMORY;
    }

    int compare_result;
    Node prev_node = NULL;
    Node tmp_it = map->head;
    while (tmp_it != NULL){
        compare_result = map->compareKeyElements(tmp_it->key_element, keyElement);
        if(compare_result == 0) {
            map->freeKeyElement(copy_key);
            map->freeDataElement(tmp_it->data_element);
            tmp_it->data_element = copy_data;
            return MAP_SUCCESS;
        }
        if(compare_result > 0) {
            Node new_node = CreateNode(copy_key, copy_data);
            if(prev_node) {
                prev_node->next = new_node;
            } else {
                map->head = new_node;
            }
            new_node->next = tmp_it;
            map->size++;
            return MAP_SUCCESS;
        }

        prev_node = tmp_it;
        tmp_it = tmp_it->next;
    }

    Node new_node = CreateNode(copy_key, copy_data);
    if(prev_node) {
        prev_node->next = new_node;
    } else {
        map->head = new_node;
    }
    map->size++;

    return MAP_SUCCESS;
}

MapDataElement mapGet(Map map, MapKeyElement keyElement){
    if(map==NULL || keyElement == NULL || map->size==0)
        return NULL;
    int compare_result;
    Node tmp_it = map->head;
    while(tmp_it){
        compare_result = map->compareKeyElements(tmp_it->key_element, keyElement);
        if(compare_result > 0) {
            break;
        }
        if(compare_result == 0){
            return tmp_it->data_element;
        }
        tmp_it = tmp_it->next;
    }
    return NULL;
}

MapResult mapRemove(Map map, MapKeyElement keyElement){
    if(map==NULL || keyElement == NULL)
        return MAP_NULL_ARGUMENT;
    if(map->size == 0) {
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    Node prev_node = NULL;
    Node tmp_it = map->head;
    while (tmp_it != NULL) {
        int compare_result = map->compareKeyElements(tmp_it->key_element, keyElement);
        if(compare_result > 0){
            break;
        }
        if(compare_result == 0){
            if(prev_node) {
                prev_node->next = tmp_it->next;
            } else {
                map->head = tmp_it->next;
            }
            map->freeKeyElement(tmp_it->key_element);
            map->freeDataElement(tmp_it->data_element);
            destroyNode(tmp_it);
            map->size--;
            return MAP_SUCCESS;
        }
        prev_node = tmp_it;
        tmp_it = tmp_it->next;
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}

MapKeyElement mapGetFirst(Map map){
    if(map == NULL || map->size == 0)
        return NULL;
    map->map_it = map->head;
    return map->map_it->key_element;

}

MapKeyElement mapGetNext(Map map){
    if(map==NULL || map->map_it==NULL || map->map_it->next==NULL)
        return NULL;
    map->map_it = map->map_it->next;
    return map->map_it->key_element;
}

MapResult mapClear(Map map){
    if(map==NULL)
        return MAP_NULL_ARGUMENT;
    map->map_it = map->head;
    while(map->map_it!=NULL){
        Node tmp_node = map->map_it->next;
        map->freeKeyElement(map->map_it->key_element);
        map->freeDataElement(map->map_it->data_element);
        destroyNode(map->map_it);
        map->map_it = tmp_node;
    }
    map->map_it = map->head;
    return MAP_SUCCESS;
}

List mapConvertToSortedListByValue(Map map, CompareListElements compareListElements) {
    List sorted_list = listCreate(map->copyDataElement, map->freeDataElement);
    if(map->size == 0) {
        return sorted_list;
    }

    Map tmp_map = mapCopy(map);
    if(!tmp_map) {
        listDestroy(sorted_list);
        return NULL;
    }

    while(mapGetSize(tmp_map) > 0) {
        Node max = tmp_map->head;
        for(Node it = max->next; it; it = it->next) {
            int compare_result = compareListElements(max->data_element, it->data_element);
            if (compare_result < 0) {
                max = it;
            }
        }
        listInsertLast(sorted_list, max->key_element);
        mapRemove(tmp_map, max->key_element);
    }

    mapDestroy(tmp_map);

    return sorted_list;
}

void dumpMap(Map map, printMapElement printElement, void *context) {
    for(Node iterator = map->head; iterator; iterator = iterator->next) {
        printElement(iterator->data_element, context);
    }
}
