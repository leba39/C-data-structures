/*
 *  DATA STRUCTURES
 *  BINARY SEARCH TREE
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>       //for srand

//S T R U C T
struct node{
    int data;
    char count;
    struct node* left;
    struct node* right;
};

//F U N C T I O N s
void insertValue(struct node** head,int new_data);
void deleteValue(struct node** head,int target_value);
void print_tree(struct node *bst, int indent);

//M A I N
int main(){

    //MATOROs TEST
    srand(time(NULL));
    int values[10];
    struct node *head = NULL;
    for(int i = 0; i < 10; i++)
    {
        values[i] = rand() % 100;
        insertValue(&head, values[i]);
    }
    //print completed BST
    print_tree(head,0);

    for(int i = 0; i < 10; i++)
    {
        deleteValue(&head, values[i]);
        //print current BST after each delete
        printf("------------------\n");     
        print_tree(head,0);
    }
    
    return 0;
}

//I M P L E M E N T A T I O N s
void insertValue(struct node** head,int new_data){


    //NULL HEAD POINTER
    if(!head)   return;

    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data  = new_data;
    new->count = 1;
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
        if(navigator->data == new_data){
            navigator->count++;    
            free(new);
            return;
        }
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

void deleteValue(struct node** head,int target_value){
    
    if(!head || !(*head))   return; //evaluates left to right, avoids segfault.
    struct node* navigator       = *head;
    struct node* parentNavigator = navigator;
    struct node* nextMove        = NULL;
    bool moveLeft                = false;

    //WE TRY TO FIND TARGET VALUE:
    do{
        if(navigator->data == target_value) break;
        
        nextMove  = ((navigator->data) > target_value) ? (navigator->left) : (navigator->right);
        moveLeft  = ((navigator->data) > target_value) ? true : false;

        if(nextMove!=NULL){
            parentNavigator = navigator;
            navigator = nextMove; 
        }else{
            printf("Target value (%d) is not in the given BST.\n",target_value);
            return;
        }
    }while(true);
    
    /*
        IF WE REACH THIS POINT WE HAVE FOUND THE TARGET VALUE. *NAVIGATOR holds that node:
    */
        
    //Decrease count and return if there are duplicates.
    if ((navigator->count)>1){ 
            navigator->count -= 1;
            return;
    }

    /*----CASUISTICA: CHILD-LESS NODE----*/
    if(navigator->left == NULL && navigator->right == NULL){

        if(navigator == parentNavigator){   
            //Last node of the BST.
            free(navigator);
            *head = NULL;                   //Important! navigator = NULL didn't work as expected!
        }else{
            //Generic childless node. 
            free(navigator);
            navigator = NULL;
            if(moveLeft){
                parentNavigator->left  = NULL;
            }else{
                parentNavigator->right = NULL;
            }
        }
        return;
    }

    /*---- CASUISTICA: NODE HAS ONE CHILD----*/
    if(navigator->left == NULL && navigator->right != NULL){
        
        //We are dealing with the HEAD node.
        if(navigator == parentNavigator){
            *head = navigator->right;
            free(navigator);
            navigator = NULL;
            return;
        }
        //Generic one-child node.
        if(moveLeft){
            parentNavigator->left = navigator->right;
            free(navigator);
            navigator = NULL;
        }else{
            parentNavigator->right = navigator->right;
            free(navigator);
            navigator = NULL;
        }
        return;

    }else if(navigator->left != NULL && navigator->right == NULL){
        
        //We are dealing with the HEAD node.
        if(navigator == parentNavigator){
            *head = navigator->left;
            free(navigator);
            navigator = NULL;
            return;
        }
        //Generic one-child node.
        if(moveLeft){
            parentNavigator->left = navigator->left;
            free(navigator);
            navigator = NULL;
        }else{
            parentNavigator->right = navigator->left;
            free(navigator);
            navigator = NULL;
        }
        return;
    }    

    /*----CASUISTICA: NODE HAS TWO CHILDREN----*/
    if(navigator->left != NULL && navigator->right != NULL){
        //AUX LOCAL VARs
        struct node* aux;    
        moveLeft = false;
        /*
            We go down one right and then all left. We keep going down the left branch until we hit NULL.
            That is, we find the min value from the right sub-tree.
        */
        nextMove = navigator->right;    
        do{
            aux = parentNavigator;
            parentNavigator = nextMove;
            nextMove = nextMove->left;
            if(nextMove)     moveLeft = true;    //We moved left from the right subtree atleast once.
        }while(nextMove != NULL);

        //If the min from the right subtree is the first node we encounter. We didn't move 'left' once.
        if(!moveLeft){
            navigator->data  = parentNavigator->data;
            navigator->count = parentNavigator->count; 
            navigator->right = parentNavigator->right;
            free(parentNavigator);
            parentNavigator  = NULL;
        }else{
            navigator->data  = parentNavigator->data;
            navigator->count = parentNavigator->count;    
            aux->left = (parentNavigator->right) ? parentNavigator->right : NULL;
            free(parentNavigator);
            parentNavigator  = NULL;
        }
        return;
    }
}

void print_tree(struct node *bst, int indent){
    
    if(!bst){
        fprintf(stdout, "Lista vacia\n");   //Empty list.
        return;
    }
    for(int i = 0; i < indent; i++)     fprintf(stdout, "\t");
    fprintf(stdout, "%i\n", bst->data);
    if(bst->left)       print_tree(bst->left, indent + 1);
    if(bst->right)      print_tree(bst->right, indent + 1);
}
