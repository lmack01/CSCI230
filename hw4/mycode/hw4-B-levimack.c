/* Levi Mack */

#include "./hw4-levimack.h"

void bar(char *filename, int total, char **words) {
		
		int i;
		FILE *fout = fopen("words.txt", "w");		
		
		for (i = 0; i < total; i++){
			//printf("%d\n", arr[i]);
			fprintf(fout, "%s\n", words[i]);
		}
		fclose(fout);
}
