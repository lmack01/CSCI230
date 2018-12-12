
#include "./hw4-BrandonMord.h"	

int longestA(char *filename){
	FILE *data;
	int start, longest=0, temp = 0;
	
	data = fopen(filename, "r");
	
	start = fgetc(data); //get next(first) character
	if(start == '\n'){
		if(temp > longest){
			longest = temp;
		}
		temp = 0;
	}
	else{
		temp++;
	}
	while(start != EOF)	{ //check until end of file
		start = fgetc(data);
		if(start == '\n'){
		if(temp > longest){
			longest = temp;
		}
		temp = 0;
		}
		else{
			temp++;
		}
	}
	fclose(data);
	return longest;
}

	
int main(void){
	int longest, temp, lines1, lines2, lines3, total, i, index, index2, added = 0;
	size_t idex;
	char f1[] = "american0.txt";
	char f2[] = "american1.txt";
	char f3[] = "american2.txt";
	char out[] = "words.txt";
	char word[longest], c;
	char **words;
	FILE *data1, *data2, *data3;
	//get the number of items in the file (foo)
	lines1 = foo(f1);
	lines2 = foo(f2);
	lines3 = foo(f3);
	longest = longestA(f1) +1;
	temp = longestA(f2);
	if(temp > longest) longest = temp+1;
	temp = longestA(f3);
	if(temp > longest) longest = temp+1;
	
	total = lines1+ lines2 + lines3;
	
	//create appropriately sized arrays
	words = (char**) calloc(total, sizeof(char *));
	for(i=0; i< total; i++){
		words[i] = (char*) calloc(longest, sizeof(char));
	}
	
	//put the words into the arrays
	data1 = fopen(f1, "r");
	data2 = fopen(f2, "r");
	data3 = fopen(f3, "r");
	index =0;

	for(i=0; i< lines1; i++){
		for(idex =0; idex<longest;){
			c = fgetc(data1);
			if(c == EOF) break;
			if(!isalpha(c)){
				if(c != '\''){
					if(!idex) continue;
					else break;
				}
			}
			words[index][idex++] = c;	
		}
			words[index][idex] = '\0';
			added++;
			index++;
		
	}
	for(i=0; i< lines2; i++){
		for(idex =0; idex<longest;){
			c = fgetc(data2);
			if(c == EOF) break;
			if(!isalpha(c)){
				if(c != '\''){
					if(!idex) continue;
					else break;
				}
			}
			words[index][idex++] = c;	
		}
			words[index][idex] = '\0';
			added++;
			index++;
		
	}	
	for(i=0; i< lines3; i++){
		for(idex =0; idex<longest;){
			c = fgetc(data3);
			if(c == EOF) break;
			if(!isalpha(c)){
				if(c != '\''){
					if(!idex) continue;
					else break;
				}
			}
			words[index][idex++] = c;	
		}

			words[index][idex] = '\0';
			added++;
			index++;
		
	}

	fclose(data1);
	fclose(data2);
	fclose(data3);
	
	bar(out, added, words);

	for(i=0; i < total; i++){
		free(words[i]);
	}
	free(words);
	
	return 0;
}