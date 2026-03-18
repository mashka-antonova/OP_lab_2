#ifndef LIST_H
#define LIST_H

#include "demography.h"

typedef struct LinkedNode {
    DemographicRecord data;
    LinkedNode* next;
} LinkedNode;

typedef struct {
    int size;
    LinkedNode *head;
    LinkedNode *tail;
} LinkedList;

#endif // LIST_H
