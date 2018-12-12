/* Levi Mack */

#include "./hw4-levimack.h"


int comp(const void *x, const void *y) {
	const char *p1 = *(const char**)x;
	const char *p2 = *(const char**)y;
	
	return strcasecmp(p1, p2);
}

int main(void) {

	int i, ind, j, total, t, f0c, f1c, f2c, big, added;
	char **arr;
	size_t pos;
		
	char file1[] = "american0.txt";
	char file2[] = "american1.txt";
	char file3[] = "american2.txt";
	char outfile[] = "words.txt";
	char c;

	//count the lines of each file
	f0c = foo(file1);
	f1c = foo(file2);
	f2c = foo(file3);
	
	big = biggest(file1) + 1;
	t = biggest(file2);
	if (t > big) {
		big = t + 1;	
	}	
	t = biggest(file3);
	if (t > big) {
		big = t + 1;
	}
	
	total = f0c + f1c + f2c; //total number of lines of data in the input files
	
	//open files to read data from
	FILE *fp0, *fp1, *fp2, *fout;

	fp0 = fopen(file1, "r");
	fp1 = fopen(file2, "r");
	fp2 = fopen(file3, "r");	

	//create dynamic array
	arr = (char **) calloc(total, sizeof(char *));
	for (i = 0; i < total; i++) {
		arr[i] = (char *) calloc(big, sizeof(char));
	}
	
	added = 0;
	ind = 0; //index of the array
	
	for (i = 0; i < f0c; i++) {
		for (pos = 0; pos < big;) {
			c = fgetc(fp0);
			if (c == EOF) {
				break;
			}
			if (!isalpha(c)) {
				if (c != '\'') {
					if (!pos) {
						continue;
					}
					else {
						break;
					}
				}
			}
			arr[ind][pos++] = c;			
		}
		arr[ind][pos] = '\0';
		added++;
		ind++;
	}
	
	for (i = 0; i < f1c; i++){	
		for (pos = 0; pos < big;) {
			c = fgetc(fp1);
			if (c == EOF) {
				break;
			}
			if (!isalpha(c)) {
				if (c != '\'') {
					if (!pos) {
						continue;
					}
					else {
						break;
					}
				}
			}
			arr[ind][pos++] = c;			
		}
		arr[ind][pos] = '\0';
		added++;
		ind++;
	}

	for (i = 0; i < f2c; i++){	
		for (pos = 0; pos < big;) {
			c = fgetc(fp2);
			if (c == EOF) {
				break;
			}
			if (!isalpha(c)) {
				if (c != '\'') {
					if (!pos) {
						continue;
					}
					else {
						break;
					}
				}
			}
			arr[ind][pos++] = c;			
		}
		arr[ind][pos] = '\0';
		added++;
		ind++;
	}

	fclose(fp0);	
	fclose(fp1);	
	fclose(fp2);

	qsort(arr,added,sizeof(char*),comp);
	
	bar(outfile, added,  arr);

	for (j = 1; j < total; j++) {
		free(arr[j]);
	}
	free(arr);	
	return 0;
}

int biggest(char *filename) {

	FILE *fin;
	int first, biggest, t;

	biggest = 0;
	t = 0;
	
	fin = fopen(filename, "r");
	first = fgetc(fin);
	
	if (first == '\n') {
		if (t > biggest) {
			biggest = t;
		}
		t = 0;
	}
	else {
		t++;
	}
	
	while (first != EOF) {
		first = fgetc(fin);
		if (first == '\n'){
			if (t > biggest) {
				biggest = t;
			}
			t = 0;
		}
		else {
			t++;
		}
	}
	fclose(fin);
	return biggest;
}

/*
MARSH'S CODE - DO NOT COPY - USE FOR REFERENCE

// hw4.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *data;
char word[50]; 


----------------------------------------------------------

// hw4.c

#include "./hw4.h"

int main(void) {
int   i, j;
int   cnt0, cnt1, cnt2, total;
char **words;

    // Determine file sizes.
    cnt0 = foo("./american0.txt");
    cnt1 = foo("./american1.txt");
    cnt2 = foo("./american2.txt");

    // Create dynamic array for words.
    total = cnt0 + cnt1+ cnt2;
    words = calloc(total, sizeof(*words));
    for (i = 0; i < total; i++) {
        words[i] = calloc(50, sizeof(char));
    }

    // Populate dynamic array from three files.
    j = 0;
    data = fopen("./american0.txt", "r");
    for (i = 0; i < cnt0; i++) {
       fscanf(data, "%s", words[j++]);
    } 
    fclose(data);
    data = fopen("./american1.txt", "r");
    for (i = 0; i < cnt1; i++) {
       fscanf(data, "%s", words[j++]);
    } 
    fclose(data);
    data = fopen("./american2.txt", "r");
    for (i = 0; i < cnt2; i++) {
       fscanf(data, "%s", words[j++]);
    } 
    fclose(data);

    // Sort list.
    for (i = 0; i < total; i++) {
        for (j = 0; j < total-1; j++) {
            if (strcmp(words[j], words[j+1]) > 0) {
               strcpy(word, words[j+1]);
               strcpy(words[j+1], words[j]);
               strcpy(words[j], word);
            }
        }
    }

    // Save result.
    bar("words.txt", total, words);

    // Free memory.
    for (i = 0; i < total; i++) {
        free(words[i]);
    }
    free(words);
    return 0;
}

----------------------------------------------------------

// hw4-A.c

#include "./hw4.h"

int foo(char *filename) { 
int cnt = 0;
    data = fopen(filename, "r");
    while (1) {
       fscanf(data, "%s", word);
       if (feof(data)) break;
       cnt++;
    } 
    fclose(data);
    return cnt;
}

----------------------------------------------------------

// hw4-B.c

#include "./hw4.h"

void bar(char *filename, int total, char **words) {
int i;
    data = fopen(filename, "w");
    for (i = 0; i < total; i++) {
        fprintf(data, "%s\n", words[i]);
        printf("%s\n", words[i]);
    }
    fclose(data);
}

----------------------------------------------------------

// hw4 script

gcc -c hw4-A.c

gcc -c hw4-B.c

gcc hw4.c hw4-A.o hw4-B.c -o hw4

*/

