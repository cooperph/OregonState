#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
    list->sentinel = malloc(sizeof(struct Link));
    assert(list->sentinel != 0);
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    list->size = 0;
    
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
    struct Link *newLink = malloc(sizeof(struct Link));
    assert(newLink != 0);
    newLink->next = NULL;
    newLink->prev = NULL;
    newLink->value = value;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
    //struct Link *newLink = malloc(sizeof(struct Link));
    //assert(newLink != 0);
    //newLink->value = value;
    struct Link *newLink = createLink(value);
    newLink->next = link->next;
    newLink->prev = link;
    newLink->next->prev = newLink;
    link->next = newLink;
     
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
    link->prev->next = link->next;
    link->next->prev = link->prev;
    
    free(link);
    link = NULL;
    
    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this
    free(list);
    list = NULL;
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
    assert(list != 0);
    list->sentinel->next->next->prev = list->sentinel;
    list->sentinel->next = list->sentinel->next->next;
    
    list->size--;
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
    assert(list != 0);
    list->sentinel->prev->prev->next = list->sentinel;
    list->sentinel->prev = list->sentinel->prev->prev;
    
    list->size--;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
    if (list->size > 0)
        return 0;
    else
        return 1;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
    assert(list != 0);
    struct Link *temp = list->sentinel->next;
    
    for(int i = 0; i < list->size;i++)
    {
        printf("%f ", temp->value);
        temp = temp->next;
    }
    
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
    int size = list->size;
    struct Link *temp;
    temp = list->sentinel->next;
    for(int i = 0; i<size;i++)
    {
        circularListAddFront(list, temp->value);
        temp = temp->next;;
    }
    for(int i = 0; i < size; i++)
        circularListRemoveBack(list);
}
