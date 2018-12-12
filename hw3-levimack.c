/* Levi Mack */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void) {
	//open files to read data from
	FILE *fp0, *fp1, *fp2, *fout;
	fp0 = fopen("list0.txt", "r");
	fp1 = fopen("list1.txt", "r");
	fp2 = fopen("list2.txt", "r");

	int i, ind, j, total, temp, *arr, fp0c, fp1c, fp2c;	
	i = 0;
	fp0c = 0;
	fp1c = 0;
	fp2c = 0;
	
	fscanf (fp0, "%d", &i);
	while (!feof (fp0)) {
		fp0c++;
		fscanf (fp0, "%d", &i);
	}
	
	fscanf (fp1, "%d", &i);
	while (!feof (fp1)) {
		fp1c++;
		fscanf (fp1, "%d", &i);
	}
	
	fscanf (fp2, "%d", &i);
	while (!feof (fp2)) {
		fp2c++;	
		fscanf (fp2, "%d", &i);
	}
	
	total = fp0c + fp1c + fp2c; //total number of lines of data in the input files
	fclose(fp0);	
	fclose(fp1);	
	fclose(fp2);

	//reopen files to reread through them
	fp0 = fopen("list0.txt", "r");
	fp1 = fopen("list1.txt", "r");
	fp2 = fopen("list2.txt", "r");	
	//create output file
	fout = fopen("hw3.out", "w");

	//create dynamic array
	arr = (int *) calloc((total), sizeof(int));
	
	j = 0;
	ind = 0; //index of the array
	
	for (i = 0; i < fp0c; i++){
		while (fscanf(fp0,"%d", &j) && !feof (fp0)) {
			arr[ind] = j;
			ind++;
		}
	}
	
	for (i = 0; i < fp1c; i++){	
		while (fscanf(fp1, "%d", &j) && !feof (fp1)) {
			arr[ind] = j;
			ind++;
		}
	}

	for (i = 0; i < fp2c; i++){	
		while (fscanf(fp2, "%d", &j) && !feof (fp2)) {
			arr[ind] = j;
			ind++;
		}	
	}

	//bubble sort
	for (i = 0; i < total-1; i++) {
		for (j = 0; j < (total - i-1); j++) {
			if (arr[j] > arr[j+1]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}

	for (i = 0; i < total; i++){
		//printf("%d\n", arr[i]);
		fprintf(fout, "%d\n", arr[i]);
	}	
	

	fclose(fp0);	
	fclose(fp1);	
	fclose(fp2);
	fclose(fout);
	free(arr);
	
	return 0;
}


/**
MARSH'S CODE: DONT USE, but REFERENCE

#include <stdio.h>
#include <stdlib.h>

int main(void) {
int   i, j;
int   cnt0, cnt1, cnt2, total;
int   number, *array;
FILE *data;

    // Determine size of list0.txt.
    data = fopen("./list0.txt", "r");
    cnt0 = 0; 
    while (1) {
       fscanf(data, "%d", &number);
       if (feof(data)) break;
       cnt0++;
    } 
    fclose(data);

    // Determine size of list1.txt.
    data = fopen("./list1.txt", "r");
    cnt1 = 0; 
    while (1) {
       fscanf(data, "%d", &number);
       if (feof(data)) break;
       cnt1++;
    } 
    fclose(data);

    // Determine size of list2.txt.
    data = fopen("./list2.txt", "r");
    cnt2 = 0; 
    while (1) {
       fscanf(data, "%d", &number);
       if (feof(data)) break;
       cnt2++;
    } 
    fclose(data);

    // Create dynamic array for words.
    total = cnt0 + cnt1+ cnt2;
    array = calloc(total, sizeof(number));

    // Populate dynamic array from three files.
    j = 0;
    data = fopen("./list0.txt", "r");
    for (i = 0; i < cnt0; i++) {
       fscanf(data, "%d", &array[j++]);
    } 
    fclose(data);
    data = fopen("./list1.txt", "r");
    for (i = 0; i < cnt1; i++) {
       fscanf(data, "%d", &array[j++]);
    } 
    fclose(data);
    data = fopen("./list2.txt", "r");
    for (i = 0; i < cnt2; i++) {
       fscanf(data, "%d", &array[j++]);
    } 
    fclose(data);

    // Sort list.
    for (i = 0; i < total; i++) {
        for (j = 0; j < total-1; j++) {
            if (array[j] > array[j+1]) {
               number = array[j+1];
               array[j+1] = array[j];
               array[j] = number;
            }
        }
    }

    // Save result.
    data = fopen("./hw3.out", "w");
    for (i = 0; i < total; i++) {
        fprintf(data, "%d\n", array[i]);
    }
    fclose(data);

    // Free dynamic array.
    free(array);

    return 0;
}

*/