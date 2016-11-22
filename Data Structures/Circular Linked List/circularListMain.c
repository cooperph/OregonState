#include "circularList.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{	
	struct CircularList* deque = circularListCreate();
    
	circularListAddBack(deque, (TYPE)1);
	circularListAddBack(deque, (TYPE)2);
	circularListAddBack(deque, (TYPE)3);
	circularListAddFront(deque, (TYPE)4);
	circularListAddFront(deque, (TYPE)5);
	circularListAddFront(deque, (TYPE)6);
	circularListPrint(deque);
	printf("\nFront: %g\n", circularListFront(deque));
	printf("Back: %g\n", circularListBack(deque));
    
	circularListRemoveFront(deque);
	circularListRemoveBack(deque);
	circularListPrint(deque);
	
    printf("\n");
    
	circularListReverse(deque);
	circularListPrint(deque);
	
	circularListDestroy(deque);
	
	return 0;
}
