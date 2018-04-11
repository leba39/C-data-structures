#include <stdio.h>
#include <stdlib.h>

//BASIC LINKED LIST
struct node{
	int data;
	struct node* next;
};

void printQueue(struct node* head){
		
	struct node* pointer = head;
	int i = 1;
	if (!pointer||!pointer->data) return;
	do{
		printf("Elemento %d:	%d\n",i,pointer->data);
		pointer = pointer->next;
		i++;
	}while(pointer!=NULL);
}

void push(struct node **head, int new_data)
{
    if (!head)  return;   
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data = new_data;
    new->next = NULL;
    if(!(*head))
    {
       *head = new;
       return;
    }
    struct node *ptr = *head;
    while(ptr->next)
    {
        ptr = ptr->next;
    }
    ptr->next = new;
    return;
}

void pop(struct node **head){
    
	if(!head||!(*head)) return;	//we dont delete from an empty list or a NULL input. salvamos el codigo al evaluar de izqd a derecha. Si cambio el orden da SEGFAULT

	if(!(*head)->next){		//list with one element.
		free(*head);
		*head = NULL;
		return;
	}

	//multiple elements.
	struct node* pointer = *head;
	*head = (*head)->next;
	free(pointer);
    return;
}
	
int main(){

	//I could also implement the queue by using add_front_list and remove_end_list instead.
    
    //EMPTY NULL NODE POINTER
    struct node* queueHead = NULL;


    //errorChecks
    pop(NULL);
    pop(&queueHead);
    push(NULL,0);
    //PUSHs
	push(&queueHead,1);
	push(&queueHead,2);
	push(&queueHead,3);
	push(&queueHead,4);
	push(&queueHead,5);
	push(&queueHead,6);
	//PRINT QUEUE
	printf("QUEUE STATUS:\n");
	printQueue(queueHead);
	//POPs
	pop(&queueHead);
	pop(&queueHead);
    pop(&queueHead);
    pop(&queueHead);
    pop(&queueHead);
    //PRINT QUEUE
	printf("QUEUE STATUS:\n");
	printQueue(queueHead);
	//FINAL POP
    pop(&queueHead);
    //PRINT QUEUE
	printf("QUEUE STATUS:\n");
	printQueue(queueHead);  //should be empty

	return 0;
}
