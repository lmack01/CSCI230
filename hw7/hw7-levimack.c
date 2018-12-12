/* Levi Mack */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct node {
	char name[42];
	struct node *next;
};
typedef struct node NODE;

void ADD(NODE *(*head), char *name) {
	NODE *curr;
	NODE *temp;
	NODE *prev;
	curr = (NODE *)malloc(sizeof(NODE));
	strcpy(curr->name, name);
	
	//if list is empty
	if ((*head) == NULL || (strcmp(curr->name,(*head)->name)) < 0) {
		curr->next = (*head);
		(*head) = curr;	
		return;
	}
	if ((strcmp(curr->name,(*head)->name)) > 0) {
		temp = (*head);
		prev = temp;
		while (temp != NULL) {
			if ((strcmp(curr->name,temp->name)) == 0) return;
			if((strcmp(curr->name,temp->name)) < 0) {
				curr->next = temp;
				prev->next = curr;				
				//printf("successfully added.\n\n");				
				return;
			}
			prev = temp;
			temp = temp->next;
		}
		//if it makes it through the while loop, add at the end
		prev->next = curr;
		curr->next = NULL;
		//printf("successfully added.\n\n");
		return;
	}
}

void DELETE(NODE *(*head), char *name) {
	NODE *curr;
	NODE *temp;
	
	//locate node to delete
	curr = (*head);
	while (curr != NULL) {
		if (strcmp(curr->name,name) == 0 ) {
			break;
		}
		temp = curr;
		curr = curr->next;
	}
	//printf("FOUND: %s\n",curr->name);
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
}

void TRAVERSE(NODE *head) {
	NODE *curr;
	curr = head;
	int count = 1;
	while (curr != NULL) {
		printf("%d %s\n", count, curr->name);
		curr = curr->next;
		count++;
	}
}

void FREE(NODE *(*head)) {
	NODE *curr;
	curr = (*head);
	while (curr != NULL) {
		curr = (*head)->next;
		free((*head));
		(*head)->next = NULL;
		(*head) = curr;
	}
}

int main() {
	
	NODE *head;
	head = NULL;
	
	FILE *fp1;
	fp1 = fopen("hw7.data", "r");
	
	int i = 0;
	char *item;
	char *decision;
	char *line = NULL;
	const char str[2] =" ";
	size_t len = 0;
	ssize_t read;
	
	while ((read = getline(&line,&len,fp1)) != -1) {
		item = strtok(line, str);
		while (item != NULL) {
			//printf("%s\n", item);
			decision = strtok(NULL, str);
			//printf("decision: %s", decision);			
			
			//printf("%d\n\n",(strcmp(decision,"a")));			
			if (((strcmp(decision,"a")) == 13) || ((strcmp(decision,"a")) == 0)) {
				printf("\n\nAdding: %s\n",item);
				printf("Before add:\n");
				TRAVERSE(head);	
				
				ADD(&head, item);
				
				printf("\nAfter Add:\n");
				TRAVERSE(head);				
			}
			else {
				printf("\n\nDeleting: %s\n",item);
				printf("Before deletion:\n");
				TRAVERSE(head);
				
				DELETE(&head,item);
				
				printf("\nAfter Delete:\n");
				TRAVERSE(head);
			}
			item = strtok(NULL,str);
		}
		i++;
	}
	printf("\n\nLIST AFTER ADDS/DELETES:\n");
	TRAVERSE(head);
	FREE(&head);
	if (head == NULL) printf("\nAfter free: Empty List\n");
	else { TRAVERSE(head); }
	free(line);
	return 0;
}