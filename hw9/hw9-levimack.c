/* Levi Mack */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct myTree { 
   char *first;
   char *last;
   long number;
   struct myTree *right, *left; 
}; 
typedef struct myTree NODE;

int SCAN(FILE *(*stream)) {
	*stream = fopen("hw9.data", "r");
	char *line;
	size_t len = 0;
	ssize_t read;
	
	int lines = 0;	
	while ((read = getline(&line,&len,*stream)) != -1) {
		lines++;
	}
	//printf("%d\n", lines);
	return lines;	
}

void INSERT(NODE *(*tree), NODE *item) {
	int result;
	int test2;
	//if tree is empty
	if ((*tree) == NULL) {
		(*tree) = item;		
		//printf("%s\n\n",(*tree)->first);
		return;
	}
	else {
		result = strcmp(item->first, (*tree)->first);
		//add on the left
		if (result < 0) {
			//printf("left\n");
			INSERT(&((*tree)->left), item);
			return;
		}
		//add on the right
		if (result > 0) {
			//printf("right\n");
			INSERT(&((*tree)->right), item);
			return;
		}
		if (result == 0) {
			test2 = strcmp(item->last, (*tree)->last);
			//printf("The two items are equal\n");
			if (test2 < 0) {
				//printf("left\n");
				INSERT(&((*tree)->left), item);
				return;
			}
			//add on the right
			if (test2 > 0) {
				//printf("right\n");
				INSERT(&((*tree)->right), item);
				return;
			}
		}
	}
}

struct myTree *LOAD(FILE *stream, int size, NODE *(*tree)) {
	rewind(stream); 

	NODE *curr;
	int i = 0;
	char *item;
	char *line = NULL;
	const char str[2] =" ";
	size_t len = 0;
	ssize_t read;
	
	//struct myTree *arr = (struct myTree *) calloc(size, sizeof(struct myTree));
	while ((read = getline(&line,&len,stream)) != -1) {
		curr = (NODE*) malloc(sizeof(NODE));
		item = strtok(line, str);
		while (item != NULL) {
			curr->first=strdup(item);
			//printf("first: %s\n", item);

			item = strtok(NULL, str);
			curr->last = strdup(item);
			//printf("last: %s\n", item);

			item = strtok(NULL,str);
			curr->number = atol(item); 
			//printf("number: %s\n", item);
			
			item = strtok(NULL,str);
		}
		INSERT(&(*tree), &(*curr));
		i++;		
	}
	return *tree;	
}


void PRE_ORDER(NODE *tree) {
	printf("%s %s %li\n",tree->first, tree->last, tree->number);
	if (tree->left != NULL) {
		PRE_ORDER(tree->left);
	}
	if (tree->right != NULL) {
		PRE_ORDER(tree->right);
	}
}

void IN_ORDER(NODE *tree) {
	if (tree->left != NULL) {
		IN_ORDER(tree->left);
	}
	printf("%s %s %li\n",tree->first, tree->last, tree->number);
	if (tree->right != NULL) {
		IN_ORDER(tree->right);
	}
}

void POST_ORDER(NODE *tree) {
	if (tree->left != NULL) {
		POST_ORDER(tree->left);
	}
	if (tree->right != NULL) {
		POST_ORDER(tree->right);
	}
	printf("%s %s %li\n",tree->first, tree->last, tree->number);
}

void FREE(NODE *tree) {
	if (tree == NULL) return;
	FREE(tree->left);
	FREE(tree->right);
	//printf("FREEING: %s\n",tree->first);
	free(tree);
}

int main(void) {
int size;
FILE *stream;
NODE *tree = NULL;
    size = SCAN(&stream);
    LOAD(stream, size, &tree);
    system("clear"); // Clear the screen.
    printf("\nPRE_ORDER\n");
    printf("--------------\n");
    PRE_ORDER(tree); 
    printf("\nIN_ORDER\n");
    printf("--------------\n");
    IN_ORDER(tree); 
    printf("\nPOST_ORDER\n");
    printf("--------------\n");
    POST_ORDER(tree); 
    FREE(tree);
    tree = NULL;
}
