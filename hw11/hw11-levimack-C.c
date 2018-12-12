/* Levi Mack 
	DISPLAY Functions
*/

#include "./hw11-levimack-C.h"

void DISPLAY_INORDER(NODE *head) {
	NODE *curr;
	curr = head;
	while (curr != NULL) {
		printf("Left to right output:\t%d\n", curr->number);
		curr = curr->next;
	}
}

void DISPLAY_POSTORDER(NODE *tail) {
	NODE *curr;
	curr = tail;
	while (curr != NULL) {
		printf("Right to left output:\t%d\n", curr->number);
		curr = curr->prev;
	}
}

void DISPLAY_TRASH(NODE *trashHead) {
	NODE *curr;
	curr = trashHead;
	printf("\n-------------TRASH----------------\n");
	while (curr != NULL) {
		printf("Item to delete:\t%d\n", curr->number);
		curr = curr->next;
	}
	printf("----------------------------------\n");		
}