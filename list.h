#ifndef LIST_H
#define LIST_H

#include "demography.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LinkedNode {
    DemographicRecord data;
    struct LinkedNode* next;
    struct LinkedNode* prev;
} LinkedNode;

typedef struct {
    int size;
    LinkedNode *head;
    LinkedNode *tail;
} LinkedList;

LinkedList* initLinkedList();
void disposeList(LinkedList* list);

void insertAtHead(LinkedList* list, LinkedNode* newNode);
void insertAfter(LinkedList* list, LinkedNode* prevNode, LinkedNode* newNode);
int insertSort(LinkedList* list, DemographicRecord record);


#ifdef __cplusplus
}
#endif

#endif // LIST_H
