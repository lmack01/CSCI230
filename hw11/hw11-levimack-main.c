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

int main(int argv, char **argc) {
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
		if (SIZE(head) > 3) {	
				
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
	if (argv > 2) {
		printf("******************************************\n");
		printf("* You have provided too many parameters. *\n");
		printf("******************************************\n");
		return 0;
	}	

	FREE_INORDER(&head, &tail);
	if (head == NULL && tail == NULL) printf("\nOriginal List After free: Empty List\n");
	else { DISPLAY_INORDER(head); }
	return 0;
}