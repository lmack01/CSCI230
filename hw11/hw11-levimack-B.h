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

void mtogc(NODE *(*curr), NODE *(*trashHead));

void DELETE(NODE *(*head), NODE *(*tail), NODE *(*trashHead), int number);

void randDelete(NODE *(*head), NODE *(*tail), NODE *(*trashHead));