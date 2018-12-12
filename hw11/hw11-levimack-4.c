/* Levi Mack */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include <dlfcn.h>

struct node {
	int number;
	struct node *next;
	struct node *prev;
};
typedef struct node NODE;

int main(int argv, char **argc) {
	
	void *handle;
	handle=dlopen("./hw11-lib-levimack.so",RTLD_LAZY);
	void(*add)();
	add=dlsym(handle,"ADD");
	if(!handle){
		printf("HERE\n");
		printf("HERE %s\n",dlerror());
	}
	
	//doubly linked list
	NODE *head;
	head = NULL;
	NODE *tail;
	tail = NULL;
	
	if (argv <= 1) {
		printf("**********************************************\n");
		printf("* You must include a number to count through *\n");
		printf("**********************************************\n");
		return 0;
	}
	if (argv == 2) {
		int num = atoi(argc[1]);
		printf("Command line argument:\t%d\n\n",num);
		int i;
		for (i = 0; i <= num; i++) {
			printf("Input data:\t\t%d\n",i);
			add(&head, &tail, i);
		}
		printf("\n");
		
		void (*printIO)();
		printIO = dlsym(handle, "DISPLAY_INORDER");
		printIO(head);
		//DISPLAY_INORDER(head);
		printf("\n");
		
		void (*printPO)();
		printPO = dlsym(handle, "DISPLAY_POSTORDER");
		printPO(tail);
		//DISPLAY_POSTORDER(tail);
		printf("\n");
		
		int (*getSize)();
		getSize = dlsym(handle, "SIZE");
		printf("SIZE: %d\n",getSize(head));
		if (getSize(head) > 3) {	
				
			//trash list
			NODE *trashHead;
			trashHead = NULL;
	
			void (*RDel)();
			RDel = dlsym(handle, "randDelete");
			RDel(&head, &tail, &trashHead);
			//randDelete(&head, &tail, &trashHead);
			printf("\n");

			void (*freeT)();
			freeT = dlsym(handle, "FREE_TRASH");
			freeT(&trashHead);
			//FREE_TRASH(&trashHead);

			printf("\nTrash List after free:");
			void (*printT)();
			printT = dlsym(handle, "DISPLAY_TRASH");
			printT(trashHead);
			//DISPLAY_TRASH(trashHead);
			printf("\n");
		
			printf("\nOriginal List:\n");		
			printIO(head);
			//DISPLAY_INORDER(head);
			printf("\n");
			
			printPO(tail);
			//DISPLAY_POSTORDER(tail);
			printf("\n");
			
			printf("SIZE (after delete): %d\n",getSize(head));
		}
		else {
			printf("List must be at least a length of 3 for random deletion.");
		}
		
	}
	if (argv > 2) {
		printf("******************************************\n");
		printf("* You have provided too many parameters. *\n");
		printf("******************************************\n");
		return 0;
	}	
	
	void (*freeIO)();
	freeIO = dlsym(handle, "FREE_INORDER");
	freeIO(&head, &tail);
	//FREE_INORDER(&head, &tail);
	if (head == NULL && tail == NULL) printf("\nOriginal List After free: Empty List\n");
	else { printf("FREE Error"); }
	if (handle) {
		dlclose(handle);
	}
	return 0;
}