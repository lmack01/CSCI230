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

void DISPLAY_INORDER(NODE *head);

void DISPLAY_POSTORDER(NODE *tail);

void DISPLAY_TRASH(NODE *trashHead);