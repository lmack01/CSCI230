/* Levi Mack 
   FREE Functions
*/

#include "./hw11-levimack-D.h"

void FREE_TRASH(NODE *(*trashHead)) {
	NODE *curr;
	curr = (*trashHead);
	while (curr != NULL) {
		curr = (*trashHead)->next;
		free((*trashHead));
		(*trashHead)->next = NULL;
		(*trashHead)->prev = NULL;
		(*trashHead) = curr;
	}
}

void FREE_INORDER(NODE *(*head), NODE *(*tail)) {
	NODE *curr;
	curr = (*head);
	while (curr != NULL) {
		curr = (*head)->next;
		free((*head));
		(*head)->next = NULL;
		(*head)->prev = NULL;
		(*head) = curr;
	}
	(*tail)->next = NULL;
	(*tail)->prev = NULL;
	(*tail) = NULL;
}