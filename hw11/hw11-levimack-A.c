/* Levi Mack 
	Linked List Functions
*/

#include "./hw11-levimack-A.h"

void ADD(NODE *(*head), NODE *(*tail), int number) {
	NODE *curr;
	NODE *temp;
	NODE *before;
	curr = (NODE *)malloc(sizeof(NODE));
	curr->number = number;
	
	//if list is empty
	if ((*head) == NULL && (*tail) == NULL) {
		curr->next = (*tail);
		curr->prev = (*head);
		(*head) = curr;	
		(*tail) = curr;
		return;
	}
	//add at the beginning
	if (curr->number < (*head)->number){
		curr->next = (*head);
		(*head)->prev = curr;
		(*head) = curr;
		(*head)->prev = NULL;
	}
	//
	if (curr->number > (*head)->number) {
		temp = (*head);
		before = temp;
		while (temp != NULL) {
			if (curr->number == temp->number) return; //this if allows no duplicates
			if(curr->number < temp->number) { //this if adds in between the head and tail
				curr->next = temp;
				curr->prev = before;
				before->next = curr;
				temp->prev = curr;
				//printf("successfully added.\n\n");				
				return;
			}
			before = temp;
			temp = temp->next;
		}
		//if it makes it through the while loop, add at the end
		before->next = curr;
		curr->prev = before;
		curr->next = NULL;
		(*tail) = curr;
		//printf("successfully added.\n\n");
		return;
	}
}

int SIZE(NODE *head) {
	int size = 0;
	NODE *curr;
	curr = head;
	while (curr != NULL) {
		size++;
		curr = curr->next;
	}
	return size;
}