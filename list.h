#ifndef LIST_H
#define LIST_H

#include "demography.h"

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

#endif // LIST_H
