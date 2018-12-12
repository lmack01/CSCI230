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

void ADD(NODE *(*head), NODE *(*tail), int number);

int SIZE(NODE *head);
