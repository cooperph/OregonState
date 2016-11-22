#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifndef TYPE
#define TYPE int
#endif

#ifndef LT
#define LT(A, B) ((A) < (B))
#endif

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif

struct LinkedList;

struct LinkedList* linkedListCreate();
void linkedListDestroy(struct LinkedList* list);
void linkedListPrint(struct LinkedList* list);
void init(struct LinkedList* list);

// Deque interface

int linkedListIsEmpty(struct LinkedList* list);         //works
void linkedListAddFront(struct LinkedList* list, TYPE value);   //works
void linkedListAddBack(struct LinkedList* list, TYPE value);  //works
TYPE linkedListFront(struct LinkedList* list);  //works
TYPE linkedListBack(struct LinkedList* list);   //works
void linkedListRemoveFront(struct LinkedList* list);    //works
void linkedListRemoveBack(struct LinkedList* list);     //works

// Bag interface

void linkedListAdd(struct LinkedList* list, TYPE value); //works
int linkedListContains(struct LinkedList* list, TYPE value);  //works
void linkedListRemove(struct LinkedList* list, TYPE value); 

#endif