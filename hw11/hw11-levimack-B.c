/* Levi Mack 
	TRASH list Functions
*/

#include "./hw11-levimack-B.h"

void mtogc(NODE *(*curr), NODE *(*trashHead)) {
	//if trash is empty
	if ((*trashHead) == NULL) {
		(*trashHead) = (*curr);
		(*trashHead)->next = NULL;
		(*trashHead)->prev = NULL;
	}
	else {
		//1 items in the list
		if ((*trashHead) != NULL && (*trashHead)->next == NULL) {
			(*trashHead)->next = (*curr);
			(*curr)->prev = NULL;
			return;
		}
		//more than 1 items in the list
		NODE *temp;
		NODE *before;	
		temp = (*trashHead)->next;
		while (temp != NULL) {
			//add at the end (after head)
			before = temp;
			temp = temp->next;
		}
		before->next = (*curr);
		(*curr)->prev = NULL;
		(*curr)->next = NULL;
	}
}

void DELETE(NODE *(*head), NODE *(*tail), NODE *(*trashHead), int number) {
	NODE *curr;
	
	//locate node to delete
	curr = (*head);
	while (curr != NULL) {
		if (curr->number == number) {
			break;
		}
		curr = curr->next;
	}
	if (curr != NULL) { 			//essentially, if the item to delete exists in the list
		//first item delete?
		if (curr == (*head)) {
			(*head) = (*head)->next;
			curr->next = NULL;
			curr->prev = NULL;
			(*head)->prev = NULL;
			mtogc(&curr, &(*trashHead)); //move to garbage collector
			return;
		}
		//last item delete?
		if (curr == (*tail)) {			
			(*tail) = (*tail)->prev;
			(*tail)->next = NULL;
			curr->next = NULL;
			curr->prev = NULL;
			mtogc(&curr, &(*trashHead));			
			return;
		}
		//somewhere in the middle delete
		if (curr != (*tail) && curr != (*head)) {
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr->next = NULL;
			curr->prev = NULL;
			mtogc(&curr, &(*trashHead));
			return;
		}
	}
	//else { 			//item no longer exists/never existed in the list.
	//	printf("Name not found to be removed from list.\n");
	//}
}

void randDelete(NODE *(*head), NODE *(*tail), NODE *(*trashHead)) {
	int i;
	int number2Add = SIZE(*head); //size of the current list
	int number2Delete = rand() % number2Add + 3; //number of ITEMS to be deleted
	for (i = 0; i < number2Delete; i++) {
		// Pick a random node (payload) to delete.
		int link2Delete = (rand() % number2Add);
		DELETE(&(*head), &(*tail), &(*trashHead), link2Delete);
	}	
	DISPLAY_TRASH(*trashHead);
}