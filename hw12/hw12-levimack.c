/* Levi Mack */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

struct node {
	int number;
	struct node *next;
	struct node *prev;
};
typedef struct node NODE;

double mysecond(void) {
	struct timeval tp;
	struct timezone tzp;
	int i;
	   i = gettimeofday(&tp,&tzp);
	   return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

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

int main(int argv, char **argc) {
	
	double time1 = mysecond();
	double time2;
	double time;
	//doubly linked list
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
		int listSize = num+1;
		int x;
		for (x = 0; x <= num; x++){		
			int i;
			for (i = 0; i <= num; i++) {
				printf("Input data:\t\t%d\n",i);
				ADD(&head, &tail, i);
			}
			printf("\n");
			
			DISPLAY_INORDER(head);
			printf("\n");
			
			DISPLAY_POSTORDER(tail);
			printf("\n");
			
			printf("SIZE: %d\n",SIZE(head));
			if (listSize > 3) {	
					
				//trash list
				NODE *trashHead;
				trashHead = NULL;
		
				randDelete(&head, &tail, &trashHead);
				printf("\n");

				FREE_TRASH(&trashHead);

				printf("\nTrash List after free:");
				DISPLAY_TRASH(trashHead);
				printf("\n");
			
				printf("\nOriginal List:\n");		
				DISPLAY_INORDER(head);
				printf("\n");
				
				DISPLAY_POSTORDER(tail);
				printf("\n");
				
				printf("SIZE (after delete): %d\n",SIZE(head));
			}
			else {
				printf("List must be at least a length of 3 for random deletion.");
			}
		}
		time2 = mysecond();
		time = time2 - time1;
	}
	if (argv > 2) {
		printf("******************************************\n");
		printf("* You have provided too many parameters. *\n");
		printf("******************************************\n");
		return 0;
	}	

	FREE_INORDER(&head, &tail);
	if (head == NULL && tail == NULL) printf("\nOriginal List After free: Empty List\n");
	else { DISPLAY_INORDER(head); }
	
	printf("\nTime (in seconds): %f\n\n", time);
	return 0;
}