/* Levi Mack */

#include "./hw4-levimack.h"

int foo(char *filename) {

	FILE *peter;
	peter = fopen(filename, "r");
	char word[30];
	int lines = 0;
	
	//while (fscanf(peter, "%s\n", word) && !feof(peter)) {
	while ((fscanf(peter, "%s\n", word)) != EOF ) {
		lines++;
	}
	
	fclose(peter);
	return lines;
}
