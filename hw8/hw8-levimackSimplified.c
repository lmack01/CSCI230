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
	else { //add at the end
		(*tail)->next = curr;
		curr->prev = (*tail);
		curr->next = NULL;
		(*tail) = curr;
		return;
	}
}

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