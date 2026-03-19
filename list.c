#include "list.h"
#include <stdlib.h>
#include <string.h>
#include "iterator.h"

LinkedList* initLinkedList() {

  LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void insertAtHead(LinkedList* list, LinkedNode* newNode) {
  if (list != NULL && newNode != NULL) {
    newNode->next = list->head;
    newNode->prev = NULL;

    if (list->head != NULL)
      list->head->prev = newNode;
    else
      list->tail = newNode;

    list->head = newNode;
  }
}

void insertAfter(LinkedList* list, LinkedNode* prevNode, LinkedNode* newNode) {
  if (prevNode != NULL && newNode != NULL) {
    newNode->next = prevNode->next;
    newNode->prev = prevNode;

    if (prevNode->next != NULL)
      prevNode->next->prev = newNode;

    else
      list->tail = newNode;

    prevNode->next = newNode;
  }
}

int compareRecords(DemographicRecord* a, DemographicRecord* b) {
    int res = strcmp(a->region, b->region);
    if (res == 0)
        res = a->year - b->year;

    return res;
}

int insertSort(LinkedList* list, DemographicRecord record) {
  int isCorrect = 0;
  if (list != NULL) {
    LinkedNode* newNode = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (newNode != NULL) {
      newNode->data = record;
      Iterator it = begin(list);
      if (!hasNext(&it) || compareRecords(get(&it), &record) >= 0) {
        insertAtHead(list, newNode);
        isCorrect = 1;
      }
      else {
        while (it.current->next != NULL && compareRecords(getNext(&it), &record) < 0)
          next(&it);
        insertAfter(list, it.current, newNode);
        isCorrect = 1;
      }
      if (isCorrect)
        list->size++;
    }
  }
  return isCorrect;
}

void disposeList(LinkedList* list) {
  if (list != NULL) {
    LinkedNode* current = list->head;
    LinkedNode* nextNode = NULL;

    while (current != NULL) {
      nextNode = current->next;
      free(current);
      current = nextNode;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    free(list);
  }
}
