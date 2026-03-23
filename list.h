#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LinkedNode {
    void* data;
    struct LinkedNode* next;
    struct LinkedNode* prev;
} LinkedNode;

typedef struct {
    int size;
    size_t dataSize;
    LinkedNode *head;
    LinkedNode *tail;
} LinkedList;

LinkedList* initLinkedList(size_t dataSize);
void disposeList(LinkedList* list);

void insertAtHead(LinkedList* list, LinkedNode* newNode);
void insertAfter(LinkedList* list, LinkedNode* prevNode, LinkedNode* newNode);
int insertSort(LinkedList* list, const void* data, int (*cmp)(const void*, const void*));


#ifdef __cplusplus
}
#endif

#endif // LIST_H
