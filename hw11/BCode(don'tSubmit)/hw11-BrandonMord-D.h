
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int data;
	struct node *next;
	struct node *prev;
};
typedef struct node _node;
void FREE_INORDER(_node *(*head));
