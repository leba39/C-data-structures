#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//SORTED LINKED LIST
struct node{
	int data;
	struct node* next;
};

void printList(struct node* head){

	struct node* pointer = head;
	int i = 1;

	while(pointer!=NULL){
		printf("Elemento %d:\t%d\n",i,pointer->data);
		pointer = pointer->next;
		i++;
	}
}

void insertValue(struct node** head, int new_value){

	//DECLARATION
	bool end;
	struct node* newNode;
	struct node* pointer;
	
	//DEFINITION
	end = true;
	pointer = *head;

	//ALLOCATION
	newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = new_value;
	



	/*EMPTYLIST:	Set the Node pointer to Null, update *head reference value and return.*/
	if(!pointer){
		newNode->next = NULL;
		*head = newNode;
		return;
	}

	/*ONE ELEMENT LIST:	If the newNode goes last we set its pointer to null and the first one to newNode. 
				Otherwise set newNode to point at 'pointer' and update *head reference value. Return.*/	
	if(!pointer->next){	
		if (pointer->data <= new_value){
			newNode->next = NULL;  
			pointer->next = newNode;
			*head = pointer;
			return;
		}else{
			newNode->next = pointer;
			*head = newNode;
			return;	
		}
	}

	/*MULTIPLE ELEMENTS:	First we scan where newNode should be inserted. Then we cover the different possibilities.
				The 'i' and 'end'(endoflist) variables act as auxiliaries.*/
	int i = 0;
	while(pointer->next!=NULL){
		if (pointer->data > new_value){
			end = false;
			break;
		}
		pointer = pointer->next;
		i++;
	}

	/*CASUISTRY :		(endoflist) is true and new_value is greater than last data. 
				Set newNode pointer to Null and last node pointer to newNode. Return.*/
	if(end && (pointer->data <= new_value)){
		pointer->next = newNode;
		newNode->next = NULL;
		return;
	}else{
	/*CASUISTRY:		'end' may be true or false but the new_value IS smaller than data. We could still be facing a next-to-last insert. */
		
		newNode->next = pointer;			//update newNode pointer to that who is just one position 'greater' than him.
		
		pointer = *head;				//reassign pointer to head as for-loop is used to get to the previous pointer from that of #81	
		int j = 0;	
		for(int j=0;j<(i-1);j++)	pointer = pointer->next;
		
	/*CASUISTRY:		If the search gave us that newNode should be the first element, then i=0. In that case update *head reference value.
				Otherwise, point the current pointer (#85) to newNode. Return.*/
		if(i!=0){
			pointer->next = newNode;
			return;
		}else{
			*head = newNode;
			return;
		}
	}
}

void deleteValue(struct node** head, int target_value){

	//DECLARATION & DEFINITION
	bool found = false;
	struct node* pointer = *head;




	//*EMPTYLIST:	Nothing to delete. Return.*/
	if(!pointer){
		return;
	}

	/*ONE ELEMENT LIST:	If data equals target_value then its valid. Free pointer. Return.*/ 
	if(!pointer->next && pointer->data == target_value){
		free(pointer);
		*head = NULL;
		return;
	}

	/*MULTIPLE ELEMENTS:	First we scan if there is a valid target to be deleted. Then we cover the different possibilities.
				The 'i' and 'found' variables act as auxiliaries.*/
	int i = 0;
	while(pointer->next!=NULL){
		if (pointer->data == target_value){
			found = true;
			break;
		}
		pointer = pointer->next;
		i++;
	}

	/*CASUISTRY:		We did found a valid target and its the very first one. Free pointer. Update *head reference value
				to the next one. Null pointer. Return.*/
	if (found && i == 0){
		*head = pointer->next;
		free(pointer);
		pointer = NULL;
		return;
	}

	/*CASUISTRY:		We did found a valid target to delete but it isnt the first or last one. Free pointer. Go to its previous one.
				Point this last one to its next->next in order to avoid freed pointer.*/
	if (found){
		//free(pointer);
		struct node* prev_pointer = *head;		//reassign pointer to head as for-loop is used to get to the previous pointer from that of #144	
		for(int j=0;j<(i-1);j++)	prev_pointer = prev_pointer->next;
		prev_pointer->next = prev_pointer->next->next;
		free(pointer);

		return;
	}

	/*CASUISTRY:		There is the possibility of !found because the loop works with !pointer->next so the last element doesnt get checked.
				Here we check if data equals target_value. In that case we delete the last element. Free pointer and null it. Go to
				its previous one and make it point to Null (making it now the last element)*/
	if(!found && pointer->data == target_value){
		free(pointer);
		//pointer = NULL;
		pointer = *head;
		for(int j=0;j<(i-1);j++)	pointer = pointer->next;
		pointer->next = NULL;
		return;
	}
	
}

int main(){

	struct node* head = NULL;
	

	printf("---INSERTS---\n");

	insertValue(&head,6);
	insertValue(&head,10);
	insertValue(&head,12);
	insertValue(&head,11);
	insertValue(&head,20);
	insertValue(&head,50);
	insertValue(&head,2);
	insertValue(&head,15);

	printList(head);

	printf("---DELETE---\n");

	deleteValue(&head,15);
	deleteValue(&head,2);
	deleteValue(&head,50);
	
	printList(head);

	printf("---DELETE REST---\n");

	deleteValue(&head,6);
	deleteValue(&head,10);
	deleteValue(&head,11);
	deleteValue(&head,20);
	deleteValue(&head,12);

	printList(head);

	return 0;
}


