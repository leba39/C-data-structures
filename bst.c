/*
 *  DATA STRUCTURES
 *  BINARY SEARCH TREE
 */
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};


void insertValue(struct node** head, int new_data){

    

    //NULL HEAD POINTER
    if(!head)   return;

    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data  = new_data;
    new->left  = NULL;
    new->right = NULL;

    //EMPTY HEAD POINTER
    if (!(*head)){
        *head = new;
        return;
    }

    //MULTIPLE ELEMENTS
    struct node* navigator = *head;
    struct node* nextMove  = NULL;
    do{
        nextMove  = ((navigator->data) > new_data) ? (navigator->left) : (navigator->right);
        if(nextMove!=NULL)   navigator = nextMove;    
    }while(nextMove);   

    //ADD NODE
    if((navigator->data) > new_data){
        navigator->left  = new;  
    }else{
        navigator->right = new;
    }
    
    return;
}

int main(){

    struct node* head = NULL;
    insertValue(&head,50);
    insertValue(&head,20);
    insertValue(&head,60);
    insertValue(&head,10);
    insertValue(&head,15);
    insertValue(&head,80);
    insertValue(&head,70);
    
    return 0;
}
