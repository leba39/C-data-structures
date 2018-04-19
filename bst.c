/*
 *  DATA STRUCTURES
 *  BINARY SEARCH TREE
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>       //for srand


struct node{
    int data;
    char count;
    struct node* left;
    struct node* right;
};


void insertValue(struct node** head, int new_data){

    

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
    struct node* navigator = *head;
    struct node* parentNavigator = navigator;
    struct node* nextMove  = NULL;
    bool moveLeft;

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
    }while(nextMove);   //se podria hacer infinito while() ??

    //IF WE REACH THIS POINT WE HAVE FOUND THE TARGET VALUE. *NAVIGATOR holds that node.
        //we decrease count and return.
    if ((navigator->count)>1){ 
            navigator->count -= 1;
            return;
    }

        //CASUISTICA: CHILD-LESS NODE.
    if(navigator->left == NULL && navigator->right == NULL){
        
        if(navigator == parentNavigator){
            free(navigator);
            *head = NULL; //importante navigator = NULL no funcionaba igual
            return;
        }else{ 
            free(navigator);
            navigator = NULL;
            if(moveLeft){
                parentNavigator->left  = NULL;
            }else{
                parentNavigator->right = NULL;
            }
            return;
        }
    }

        //CASUISTICA: NODE HAS ONE CHILD.
    if(navigator->left == NULL && navigator->right != NULL){
        
        if(navigator == parentNavigator){
            //HEAD.
            *head = navigator->right;
            free(navigator);
            navigator = NULL;
            return;
        }

        if(moveLeft){
    
            parentNavigator->left = navigator->right;
            free(navigator);
            navigator = NULL;
            return;
        }else{
            
            parentNavigator->right = navigator->right;
            free(navigator);
            navigator = NULL;
            return;    
        }
    }else if(navigator->left != NULL && navigator->right == NULL){
        
        if(navigator == parentNavigator){
            //HEAD.
            *head = navigator->left;
            free(navigator);
            navigator = NULL;
            return;
        }
        
        if(moveLeft){

            parentNavigator->left = navigator->left;
            free(navigator);
            navigator = NULL;
            return;
        }else{
        
            parentNavigator->right = navigator->left;
            free(navigator);
            navigator = NULL;
            return;
        }
    }    

/*
    FIXEAR LA CASUISTICA PARA EL NODO CON DOS CHILDREN: SEGUIR LA PAGINA MATORO.
*/


    //CASUISTICA: NODE HAS TWO CHILDREN

    if(navigator->left != NULL && navigator->right != NULL){
        struct node* aux;    
        moveLeft = false;
        //we go down one right and then all left. We keep going down the left branch until we hit NULL
        nextMove = navigator->right;    
        do{
            aux = parentNavigator;
            parentNavigator = nextMove;
            nextMove = nextMove->left;
            if(nextMove)     moveLeft = true;    //we moved left from the right subtree atleast once.
        }while(nextMove != NULL);

        if(!moveLeft){ //If the min from the right subtree is the first node from it.
            
            navigator->data  = parentNavigator->data;
            navigator->count = parentNavigator->count; 
            navigator->right = parentNavigator->right;
            free(parentNavigator);
            parentNavigator  = NULL;
            return;
        }else{
                
            navigator->data  = parentNavigator->data;
            navigator->count = parentNavigator->count;    
            aux->left = (parentNavigator->right) ? parentNavigator->right : NULL;
            free(parentNavigator);
            parentNavigator  = NULL;
            return;
        }
    }
}

void print_tree(struct node *bst, int indent){
    
    if(!bst){
        fprintf(stdout, "Lista vacia\n");
        return;
    }

    for(int i = 0; i < indent; i++)
    {
        fprintf(stdout, "\t");
    }
    fprintf(stdout, "%i\n", bst->data);
    if(bst->left)
    {
        print_tree(bst->left, indent + 1);
    }
    if(bst->right)
    {
        print_tree(bst->right, indent + 1);
    }
}

int main(){

    
/*
    struct node* head = NULL;
    insertValue(&head,50);
    insertValue(&head,20);
    insertValue(&head,60);
    insertValue(&head,55);
    insertValue(&head,10);
    insertValue(&head,15);
    insertValue(&head,15);
    insertValue(&head,80);
    insertValue(&head,70);
    insertValue(&head,90);
    insertValue(&head,75);
    insertValue(&head,72);
    print_tree(head,0);
    //DELETE
    deleteValue(&head,55);
    printf("--------------------------------\n");
    print_tree(head,0);
    //DELETE
    deleteValue(&head,70);
    printf("--------------------------------\n");
    print_tree(head,0);
    //DELETE
    deleteValue(&head,15);
    printf("------------15 menos una--------------------\n");
    print_tree(head,0);
    //DELETE
    deleteValue(&head,15);
    printf("--------------------------------\n");
    print_tree(head,0);
    deleteValue(&head,155);
    //DELETE
    deleteValue(&head,80);
    printf("--------------------------------\n");
    print_tree(head,0);
    //DELETE
    insertValue(&head,55);
    insertValue(&head,74);
    deleteValue(&head,60);
    printf("--------------------------------\n");
    print_tree(head,0);
    //DELETE
    deleteValue(&head,50);
    printf("--------------------------------\n");
    print_tree(head,0);

    //DELETE
    deleteValue(&head,55);
    printf("--------------------------------\n");
    print_tree(head,0);
    
    //DELETE
    deleteValue(&head,90);
    printf("--------------------------------\n");
    print_tree(head,0);

    //DELETE
    deleteValue(&head,20);
    printf("--------------------------------\n");
    print_tree(head,0);

    //DELETE
    deleteValue(&head,10);
    printf("--------------------------------\n");
    print_tree(head,0);

    //DELETE
    deleteValue(&head,72);
    printf("--------------------------------\n");
    print_tree(head,0);
 
    //DELETE
    deleteValue(&head,74);
    printf("--------------------------------\n");
    print_tree(head,0);

    //DELETE
    deleteValue(&head,75);
    printf("--------------------------------\n");
    print_tree(head,0);


*/
        
    //MATOROs TEST
    srand(time(NULL));
    int values[10];
    struct node *head = NULL;
    for(int i = 0; i < 10; i++)
    {
        values[i] = rand() % 100;
        insertValue(&head, values[i]);
    }

    print_tree(head,0);

    for(int i = 0; i < 10; i++)
    {
        deleteValue(&head, values[i]);
        printf("------------------\n");
        print_tree(head,0);
    }
    

    return 0;
}
