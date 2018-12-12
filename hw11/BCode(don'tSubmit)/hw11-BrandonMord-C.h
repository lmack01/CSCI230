
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int data;
	struct node *next;
	struct node *prev;
};
typedef struct node _node;
void DISPLAY_INORDER(_node *(*head));
void DISPLAY_POSTORDER(_node *(*head));
void DISPLAY_TRASH(_node *(*deletedNode));
