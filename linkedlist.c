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
	if (!pointer) return;
	do{
		printf("Elemento %d:	%d\n",i,pointer->data);
		pointer = pointer->next;
		i++;
	}while(pointer!=NULL);
}

void add_end_list(struct node **head, int new_data)
{
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data = new_data;
    new->next = NULL;
    if(!head)
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
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data = new_data;
    new->next = *head;
    *head = new;
    return;
}

void delete_end_list(struct node **head)
{
    if(!(*head))
    {
        return;
    }
    if(!(*head)->next)
    {
        free(*head);
        *head = NULL;
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
    
	if(!(*head)) return;	//we dont delete from an empty list.

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
}
	
int main(){

	struct node* head = (struct node*)malloc(sizeof(struct node));
	head->data = 0;
	head->next = NULL;
	
	struct node* head_one_element = (struct node*)malloc(sizeof(struct node));
	head_one_element->data = 0;
	head_one_element->next = NULL;

	struct node* head_empty = NULL;

	add_end_list(&head,1);
	add_end_list(&head,2);
	add_end_list(&head,3);
	add_end_list(&head,5);
	add_end_list(&head,8);
	add_end_list(&head,13);

	//first print. Multiple element list.
	printf("FIRST PRINT. INSERTS.\n");
	print_list(head);

	//remove from end. Multiple element list
	//delete_end_list(&head);
	//print_list(head);

	//remove from beginning. Multiple element list
	delete_front_list(&head);
	
	printf("SECOND PRINT. ONE DELETE.\n");
	print_list(head);	//Same list but without '0'.

	delete_front_list(&head);
	delete_front_list(&head);
	delete_front_list(&head);
	delete_front_list(&head);
	delete_front_list(&head);
	delete_front_list(&head);
	
	delete_front_list(&head_one_element); 
	
	printf("THIRD PRINT. DELETED ALL.\n");
	print_list(head);

	return 0;
}
