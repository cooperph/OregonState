#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
    TYPE value;
    struct Link* next;
    struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
    int size;
    struct Link* frontSentinel;
    struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
void init(struct LinkedList* list) {
    // FIXME: you must write this
    list->frontSentinel = malloc(sizeof(struct Link));
    assert(list->frontSentinel != 0);
    list->backSentinel = malloc(sizeof(struct Link));
    assert(list->backSentinel != 0);
    list->frontSentinel->next = list->backSentinel;
    list->backSentinel->prev = list->frontSentinel;
    list->size = 0;
    list->frontSentinel->prev = NULL;
    list->backSentinel->next = NULL;
    
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
    // FIXME: you must write this
    assert(link != 0);
    
    struct Link *newLink = malloc(sizeof(struct Link));
    assert(newLink != 0);
    
    newLink->value = value;
    newLink->prev = link->prev;
    newLink->next = link;
    link->prev->next = newLink;
    link->prev = newLink;
    
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
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
struct LinkedList* linkedListCreate()
{
    struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
    init(newDeque);
    return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
    while (!linkedListIsEmpty(list))
    {
        linkedListRemoveFront(list);
    }
    free(list->frontSentinel);
    free(list->backSentinel);
    free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
    // FIXME: you must write this
    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    // FIXME: you must write this
    return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
    // FIXME: you must write this
    assert(! linkedListIsEmpty(list) );
    removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
    // FIXME: you must write this
    assert(! linkedListIsEmpty(list) );
    removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
    // FIXME: you must write this
    if(list->size == 0)
        return 1;
    else
        return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
    // FIXME: you must write this
    struct Link *temp;
    temp = list->frontSentinel->next;
    for(int i = 0; i < list->size; i++)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    linkedListAddFront(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    assert( list != 0);
    struct Link *temp = list->frontSentinel->next;
    
    for(int i = 0; i < list->size; i++)
    {
        if(temp->value == value)
            return 1;
        else
            temp = temp->next;
    }
    return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    assert( list != 0);
    assert(list->size >0);
    
    if ( linkedListContains(list, value) )
    {
        struct Link *temp = list->frontSentinel->next;
        
        if(temp->value == value)
        {
            removeLink(list, temp);
            return;
        }
        else
            temp = temp->next;
    }
}




