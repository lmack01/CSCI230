#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int foo(char *filename){
	FILE *in=fopen(filename,"r");
	int lines=0;
	char word[30];
	while((fscanf(in,"%s\n",word))!=EOF){
		lines++;
	}
	return lines;
}