/* Levi Mack */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


struct _data {                                 
   char *first, *middle, *last;
   long number;
} ;	

int SCAN(FILE *(*stream)) {
	*stream = fopen("hw6.data", "r");
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

struct _data *LOAD(FILE *stream, int size) {
	rewind(stream); 

	int i = 0;
	char *item;
	char *line = NULL;
	const char str[2] =" ";
	size_t len = 0;
	ssize_t read;
	
	struct _data *arr = (struct _data *) calloc(size, sizeof(struct _data));
	while ((read = getline(&line,&len,stream)) != -1) {
		item = strtok(line, str);
		while (item != NULL) {
			arr[i].first=strdup(item);
			//printf("first: %s\n", item);

			item = strtok(NULL, str);
			arr[i].middle = strdup(item);
			//printf("middle: %s\n", item);			
			
			item = strtok(NULL, str);
			arr[i].last = strdup(item);
			//printf("last: %s\n", item);

			item = strtok(NULL,str);
			arr[i].number = atol(item); //should have used atol (long int)
			//printf("number: %s\n", item);
			
			item = strtok(NULL,str);
		}
		i++;
	}
	return arr;
}

void SEARCH(struct _data *BlackBox, char *first, char *middle, char *last, int size) {
	//retrieve the dynamic array of struct passed to it (*BlackBox)
	int i = 0;
	while ( i < size ) {
		if (middle != NULL && last != NULL) {
			 if (last != NULL && !(strcmp(middle,"_") == 0)) {
				if((strcmp(BlackBox[i].first,first) == 0) && (strcmp(BlackBox[i].middle, middle) == 0) && (strcmp(BlackBox[i].last, last) == 0)) {
					printf("*******************************************\n");
					printf("The name was found at the %d entry.\n",(i));
					printf("*******************************************\n");
					return;
				}
				i++;
			}
			else {
				if (last != NULL && (strcmp(middle,"_") == 0)) {
					if((strcmp(BlackBox[i].first,first) == 0) && (strcmp(BlackBox[i].last, last) == 0)) {
						printf("*******************************************\n");
						printf("The name was found at the %d entry.\n",(i));
						printf("*******************************************\n");
						return;
					}
					i++;
				}
			}
		}
		else {
			if (strcmp(BlackBox[i].first,first) == 0) {
				printf("*******************************************\n");
				printf("The name was found at the %d entry.\n",(i));
				printf("*******************************************\n");
				return;				
			}
			i++;
		}
	}
	printf("*******************************************\n");
	printf("The name was NOT found.\n");
	printf("*******************************************\n");
}


void FREE(struct _data *BlackBox, int size) {
	free(BlackBox);
}

int main(int argv, char **argc) {	
	
	FILE *fp1;
	int lineTotal;
	struct _data *BlackBox;
	
	//read data from data file 
	lineTotal = SCAN(&fp1);
	BlackBox = LOAD(fp1, lineTotal);	
	
	if (argv <= 1) {
		printf("*******************************************\n");
		printf("* You must include a name to search for.  *\n");
		printf("*******************************************\n");
		return 0;
	}
	if (argv == 2 || argv == 3 || argv == 4) {
		SEARCH(BlackBox, argc[1], argc[2], argc[3], lineTotal);		
	}

	else {
		printf("*******************************************\n");
		printf("You have provided too many search parameters.\n");
		printf("*******************************************\n");
		return 0;
	}

	FREE(BlackBox, lineTotal);
	BlackBox = NULL;	
	//printf("%s", BlackBox[1].first);
	fclose(fp1);
	return 0;
}
