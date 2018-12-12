#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

struct node{
	int data;
	struct node *next;
	struct node *prev;
};
typedef struct node _node;

int main(int argv, char **argc){
	void *handle;
	handle=dlopen("./hw11-lib-BrandonMord.so",RTLD_LAZY);
	void(*add)();
	add=dlsym(handle,"add");
	if(!handle){
		printf("HERE\n");
		printf("HERE %s\n",dlerror());
	}
	_node *head,*curr,*tail;
	int i;
	int to;
	head=NULL;
	tail=head;
	if(argc[1]==NULL){
		printf("********************************************************\n");
		printf("Must Enter Correct Number Of Command Line Arguments!\n");
		printf("********************************************************\n");
		return(0);
	}
	else{
		to =atoi(argc[1]);
		for(i=0;i<to;i++){
			add(i,&head,&tail);
			printf("Input Data:		%d\n",i);
		}
	}
	printf("\nIN_ORDER\n");
    printf("--------------\n");
	void (*printFuncIO)();
	printFuncIO=dlsym(handle,"DISPLAY_INORDER");
	printFuncIO(&head);
	printf("\nPOST_ORDER\n");
    printf("--------------\n");
	void (*printFuncPO)();
	printFuncPO=dlsym(handle,"DISPLAY_POSTORDER");
	printFuncPO(&tail);
	
	time_t t;
	int deleteNumb;
	srand((unsigned) time(&t));
	deleteNumb = rand() % to;
	
	while(deleteNumb==0){
		deleteNumb = rand() % to;
	}
	int delete[deleteNumb];
	
	for(i=0;i<deleteNumb;i++){
		delete[i] = rand()% to;
		delete[i]=rand() % to;
	}
	void (*deleteListFunc)();
	deleteListFunc=dlsym(handle,"deleteList");
	_node *deleteNode=NULL;
	deleteListFunc(&head,&tail,delete,deleteNumb,&deleteNode);
	printf("\nTRASH LIST\n");
    printf("--------------\n");
	void(*displayTrash)();
	displayTrash=dlsym(handle,"DISPLAY_TRASH");
	displayTrash(&deleteNode);
	
	
	printf("\nIN_ORDER\n");
    printf("--------------\n");
	printFuncIO(&head);
	printf("\nPOST_ORDER\n");
    printf("--------------\n");
	printFuncPO(&tail);
	void (*freeT)();
	freeT=dlsym(handle,"FREE_INORDER");
	freeT(&head);
	if(handle){
		dlclose(handle);
	}
	return (0);
}