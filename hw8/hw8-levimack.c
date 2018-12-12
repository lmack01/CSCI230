/* Levi Mack */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct node {
	int number;
	struct node *next;
	struct node *prev;
};
typedef struct node NODE;

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

/*void DELETE(NODE *(*head), NODE *(*tail), int *number) {
	NODE *curr;
	NODE *temp;
	
	//locate node to delete
	curr = (*head);
	while (curr != NULL) {
		if (strcmp(curr->number,number) == 0 ) {
			break;
		}
		temp = curr;
		curr = curr->next;
	}
	//printf("FOUND: %s\n",curr->number);
	if (curr != NULL) {
		//first item delete?
		if (curr == (*head)) {
			(*head) = (*head)->next;
			curr->next = NULL;
			free(curr);
			return;
		}
		//last item delete?
		if (curr->next == NULL) {
			free(curr);
			curr = NULL;
			return;
		}
		//somewhere in the middle delete
		if (curr->next != NULL && curr != (*head)) {
			temp->next = curr->next;
			curr->next = NULL;
			curr = NULL;
			return;
		}
	}
	//else {
	//	printf("Name not found to be removed from list.\n");
	//}
}*/

void TRAVERSEf(NODE *head) {
	NODE *curr;
	curr = head;
	while (curr != NULL) {
		printf("Left to right output:\t%d\n", curr->number);
		curr = curr->next;
	}
}

void TRAVERSEb(NODE *tail) {
	NODE *curr;
	curr = tail;
	while (curr != NULL) {
		printf("Right to left output:\t%d\n", curr->number);
		curr = curr->prev;
	}
}

void PRINTLIST(NODE *head) {
	printf("Head -> ");
	NODE *curr;
	curr = head;
	while (curr != NULL) {
		printf("|---| -> ");
		curr = curr->next;
	}
	printf("NULL\n");
	
	printf("        ");
	curr = head;
	while (curr != NULL) {
		printf("| %d |    ",curr->number);
		curr = curr->next;
	}
	printf("    \n");	
	
	printf("NULL <- ");
	curr = head;
	while (curr != NULL) {
		printf("|___| <- ");
		curr = curr->next;
	}
	printf("Tail\n");	
}

void FREE(NODE *(*head), NODE *(*tail)) {
	NODE *curr;
	curr = (*head);
	while (curr != NULL) {
		curr = (*head)->next;
		free((*head));
		(*head)->next = NULL;
		(*head)->prev = NULL;
		(*head) = curr;
	}
	//free((*tail)); //when it gets to the point where head == tail it is already freed
	(*tail)->next = NULL;
	(*tail)->prev = NULL;
	(*tail) = NULL;
	
}

int main(int argv, char **argc) {

	NODE *head;
	head = NULL;

	NODE *tail;
	tail = NULL;

	if (argv <= 1) {
		printf("**********************************************\n");
		printf("* You must include a number to count through *\n");
		printf("**********************************************\n");
		return 0;
	}
	if (argv == 2) {
		int num = atoi(argc[1]);
		printf("Command line argument:\t%d\n\n",num);
		int i;
		for (i = 0; i <= num; i++) {
			printf("Input data:\t\t%d\n",i);
			ADD(&head, &tail, i);
		}
		printf("\n");
		
		TRAVERSEf(head);
		printf("\n");
		
		TRAVERSEb(tail);
		printf("\n");
		
		//PRINTLIST(head);
	}
	if (argv > 2) {
		printf("******************************************\n");
		printf("* You have provided too many parameters. *\n");
		printf("******************************************\n");
		return 0;
	}	

	FREE(&head, &tail);
	if (head == NULL && tail == NULL) printf("\nAfter free: Empty List\n");
	else { TRAVERSEf(head); }
	return 0;
}