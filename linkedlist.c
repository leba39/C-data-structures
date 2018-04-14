#include <stdio.h>
#include <stdlib.h>

//BASIC LINKED LIST
struct node{
	int data;
	struct node* next;
};

void print_list(struct node* head){
		
	struct node* pointer = head;
	int i = 1;
	if (!pointer||!pointer->data) {
        printf("Lista vacia!\n");
        return;
    }
	do{
		printf("Elemento %d:	%d\n",i,pointer->data);
		pointer = pointer->next;
		i++;
	}while(pointer!=NULL);
}

void add_end_list(struct node **head, int new_data)
{
    
    if(!head)   return;
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

void add_front_list(struct node **head, int new_data)
{
    if(!head)   return;
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data = new_data;
    new->next = *head;
    *head = new;
    return;
}

void delete_end_list(struct node **head)
{
    if(!head||!(*head)) //evaluates left->right. SEG FAULT if we changed positions.
    {
        return;
    }
    if(!(*head)->next)
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

void delete_front_list(struct node **head){
    
	if(!head||!(*head)) return;	//we dont delete from an empty list.Evaluates from left->right. SEG FAULT otherwise.

	if(!(*head)->next){		//list with one element.
		free(*head);
		*head = NULL;
		return;
	}

	//multiple elements.
	struct node* pointer = *head;
	//free(*head);
	*head = (*head)->next;
	free(pointer);
    return;
}
	
int main(){

	struct node* head = NULL;
	
	
    //ADDING ELEMENTS FRONT AND END:
    add_end_list(&head,4);
	add_end_list(&head,5);
	add_end_list(&head,6);
    add_front_list(&head,3);
    add_front_list(&head,2);
    add_front_list(&head,1);
	//PRINT LIST
	printf("LINKED LIST STATUS:\n");
	print_list(head);
	//REMOVING ELEMENTS FRONT-END ALTERNATIVELY
	delete_front_list(&head);
	delete_end_list(&head);
	delete_front_list(&head);
	//PRINT LIST
	printf("LINKED LIST STATUS:\n");
	print_list(head);
    //UNTIL EMPTY LIST
    delete_end_list(&head);
	delete_front_list(&head);
	delete_end_list(&head);
	//PRINT LIST
	printf("LINKED LIST STATUS:\n");    //should be empty
	print_list(head);

	return 0;
}
