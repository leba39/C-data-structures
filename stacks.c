#include <stdio.h>
#include <stdlib.h>

//BASIC LINKED LIST
struct node{
	int data;
	struct node* next;
};

void printStack(struct node* head){
		
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

void pop(struct node **head)
{
    if(!(*head))
    {
        return;
    }
    if(!(*head)->next)	//!(**head).next
    {
        free(*head);
        *head = NULL;
	return;
    }
    struct node *ptr = *head;
    while(ptr->next->next)
    {
        ptr = ptr->next;
    }
    free(ptr->next);
    ptr->next = NULL;
    return;
}
	
int main(){

	//EMPTY NULL NODE POINTER
	struct node* stackHead = NULL;
	
	//errorCheck
	pop(&stackHead);

	//PUSHs
	push(&stackHead,1);
	push(&stackHead,2);
	push(&stackHead,3);
	push(&stackHead,4);
	push(&stackHead,5);
	push(&stackHead,6);

	//PRINT STACK
	printf("STACK STATUS:\n");
	printStack(stackHead);

	//POPs

	pop(&stackHead);
	pop(&stackHead);
	pop(&stackHead);
	pop(&stackHead);
	pop(&stackHead);
	
	//PRINT STACK
	printf("STACK STATUS:\n");
	printStack(stackHead);	//should be one element remaining.

	//FINAL POP
	pop(&stackHead);
	
	//PRINT STACK
	printf("STACK STATUS:\n");
	printStack(stackHead);	//should be empty.

	return 0;
}
