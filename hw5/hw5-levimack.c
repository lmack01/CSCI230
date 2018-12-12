/* Levi Mack */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


struct _data {                                 
   char *name;
   long number;
} ;	

int SCAN(FILE *(*stream)) {
	*stream = fopen("hw5.data", "r");
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
			arr[i].name=strdup(item);
			
			item = strtok(NULL,str);
			arr[i].number = atoi(item); //should have used atol (long int)
			
			item = strtok(NULL,str);
		}
		i++;
	}
	return arr;
}

void SEARCH(struct _data *BlackBox, char *name, int size) {
	//retrieve the dynamic array of struct passed to it (*BlackBox)
	int i = 0;
	while ( i < size ) {
		if(strcmp(BlackBox[i].name,name) == 0) {
			printf("*******************************************\n");
			printf("The name was found at the %d entry.\n",(i));
			printf("*******************************************\n");
			return;
		}
		i++;
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
		//printf( "%s\n", argc[0] );
		printf("*******************************************\n");
		printf("* You must include a name to search for.  *\n");
		printf("*******************************************\n");
		return 0;
	}
	else if (argv >= 3) {
		printf("*******************************************\n");
		printf("You have provided too many search parameters.\n");
		printf("*******************************************\n");

		return 0;
	}
	else {
		//argc[1] == name to search for
		SEARCH(BlackBox, argc[1],lineTotal);
	}
	FREE(BlackBox, lineTotal);
	BlackBox = NULL;	
	//printf("%s", BlackBox[1].name);
	fclose(fp1);
	return 0;
}


/*
MARSH'S CODE - DO NOT COPY - USE FOR REFERENCE


////////////////////////////////
//  SEE HOW BIG THE FILE IS   //
////////////////////////////////

int SCAN(FILE *(*stream)) {			// We want to pass stream by reference (a pointer to a pointer).
int size = 0;
size_t chrCount;
char *text;
   // Open the file and make sure it was opened.
   if ((*stream = fopen("./hw5.data", "r")) == NULL) {
      printf("ERROR - Could not open hw5.data file.\n");
      exit(0);
   }
   // Use getline to read in a full line of data/text. 
   // This way, we don't need to guess how big each name is.
   while (1) {
      text = NULL;				// MUST be set to NULL!!!!
      getline(&text, &chrCount, *stream);	// getline expects 3 pointer arguments.
      if (feof(*stream)) break;
      size++;
   }
   return size;
}

//////////////////////
//  Load the file.  //
//////////////////////

struct _data *LOAD(FILE *stream, int size) {	// Here we can just pass stream by value (we're not changing it).
int i;
size_t chrCount;
char *text, *phone, *name;
struct _data *BlackBox;
   // Allocate memory for array of struct.
   if ((BlackBox = (struct _data*)calloc(size, sizeof(struct _data))) == NULL) {
      printf("ERROR - Could not allocate memory.\n");
      exit(0);
   }
   // Rewind the file.
   rewind(stream);
   // Use getline to read in ALL of the data/text.
   for (i = 0; i < size; i++) {
       text = NULL;				// MUST be set to NULL!!!!
       getline(&text, &chrCount, stream);
       name  = strtok(text, " ");		// strtok extracts all characters to " ".
       phone = strtok(NULL, "\n");		// strtok extracts all characters to "\n".
       // Allocate memory for name part of struct.
       if ((BlackBox[i].name = (char*)calloc(strlen(name), sizeof(char))) == NULL) {
          printf("ERROR - Could not allocate memory.\n");
          exit(0);
       }
       strcpy(BlackBox[i].name, name);		// copy name into struct.
       BlackBox[i].number = atol(phone);	// we want number as an long integer.
   }
   fclose(stream);
   return BlackBox;				// Return pointer to dynamic array.
}



////////////////////
//  Free memory.  //
////////////////////

void FREE(struct _data *BlackBox, int size) {
int i;
   for (i = 0; i < size; i++) {
       free(BlackBox[i].name);
   } 
   free(BlackBox);
   BlackBox = NULL;
}

*/