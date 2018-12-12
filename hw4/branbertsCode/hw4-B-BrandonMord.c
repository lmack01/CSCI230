
#include "./hw4-BrandonMord.h"
	
int bar(char *filename, int total, char **words){
	int i, j;
	FILE *out;
	
	out = fopen("temp.txt", "w");
	for(i=0; i<total; i++){
		fprintf(out, "%s \n", words[i]);
	}
	fclose(out);
	system("sort temp.txt > words.txt");
	system("rm temp.txt");
	return 0;
}