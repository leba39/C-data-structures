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
    int height;
};

//F U N C T I O N s
void insert_value(struct node** head,int new_data);
void delete_value(struct node** head,int target_value);
void print_tree(struct node *bst, int indent);
void rebalance(struct node **node);

void rotate_left_child(struct node **node);
void rotate_right_child(struct node **node);
void double_left_child(struct node **node);     //2 lines
void double_right_child(struct node **node);    //2 lines

int calc_height(struct node *node);


//M A I N
int main(){

    //MATOROs TEST
    srand(time(NULL));
    int values[10];
    struct node *head = NULL;


    //single rotation test. Data structures book.

    insert_value(&head,30);
    print_tree(head,0);
    
    insert_value(&head,20);
    print_tree(head,0);
    
    insert_value(&head,10);
    print_tree(head,0);
    
    insert_value(&head,40);
    print_tree(head,0);
    
    insert_value(&head,50);
    print_tree(head,0);
    
    insert_value(&head,60);
    print_tree(head,0);
    
    insert_value(&head,70);
    print_tree(head,0);

    //double rotation test.

    insert_value(&head,90);
    print_tree(head,0);

    insert_value(&head,80);
    print_tree(head,0);

    insert_value(&head,65);
    print_tree(head,0);

    insert_value(&head,85);
    print_tree(head,0);

    //DELETE

    delete_value(&head,10);
    print_tree(head,0);

    delete_value(&head,30);
    print_tree(head,0);

    delete_value(&head,85);
    print_tree(head,0);

    delete_value(&head,90);
    print_tree(head,0);

        //probar deletes de head, hacer deletes del resto. valgrind y matoro.

    
/*    
    for(int i = 0; i < 10; i++)
    {
        values[i] = rand() % 100;
        insert_value(&head, values[i]);
    }
    //print completed BST
    print_tree(head,0);

    for(int i = 0; i < 10; i++)
    {
        delete_value(&head, values[i]);
        //print current BST after each delete
        printf("------------------\n");     
        print_tree(head,0);
    }
*/  
    return 0;
}

//I M P L E M E N T A T I O N s
void insert_value(struct node** head,int new_data){


    //NULL HEAD POINTER
    if(!head)   return;

    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data  = new_data;
    new->count = 1;
    new->left  = NULL;
    new->right = NULL;
    new->height = 0;    //height is 0 for childless nodes, -1 for empty or non-existent nodes


    //EMPTY HEAD POINTER
    if (!(*head)){
        *head = new;
        return;
    }

    //MULTIPLE ELEMENTS
    struct node* navigator  = *head;
    struct node* nextMove   = NULL;
    do{
        if(navigator->data == new_data){
            navigator->count++;    
            free(new);
            return;
        }
        nextMove  = ((navigator->data) > new_data) ? (navigator->left) : (navigator->right);
        if(nextMove!=NULL)  navigator  = nextMove;
    }while(nextMove);   

    //ADD NODE
    if((navigator->data) > new_data){
        navigator->left  = new;  
    }else{
        navigator->right = new;
    }

    //UPDATE AND CHECK BALANCE FACTOR (HEIGHT)        
    struct node** balanced_tree     = head; 
    struct node** unbalanced_node   = NULL;  
    do{
        (*balanced_tree)->height = calc_height(*balanced_tree);
        int child_balance     = abs(calc_height((*balanced_tree)->right)-calc_height((*balanced_tree)->left));
        if(child_balance>1){    //tree is not balanced at this node
            unbalanced_node = balanced_tree;      
        }
        balanced_tree = ((*balanced_tree)->data > new_data) ? &(*balanced_tree)->left : &(*balanced_tree)->right;
        
    }while((*balanced_tree) != NULL);

    if(unbalanced_node) rebalance(unbalanced_node);     //will send closest unbalanced node (+-2) from the bottom up.

    return;
}

void delete_value(struct node** head,int target_value){
    
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
        goto CHECKBALANCE;
        //return;
    }

    /*---- CASUISTICA: NODE HAS ONE CHILD----*/
    if(navigator->left == NULL && navigator->right != NULL){
        
        //We are dealing with the HEAD node.
        if(navigator == parentNavigator){
            *head = navigator->right;
            free(navigator);
            navigator = NULL;
            
            goto CHECKBALANCE;
            //return;
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
        
        goto CHECKBALANCE;
        //return;

    }else if(navigator->left != NULL && navigator->right == NULL){
        
        //We are dealing with the HEAD node.
        if(navigator == parentNavigator){
            *head = navigator->left;
            free(navigator);
            navigator = NULL;
            
            goto CHECKBALANCE;
            //return;
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
        
        goto CHECKBALANCE;
        //return;
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
        
        goto CHECKBALANCE;
        //return;
    }


    CHECKBALANCE: ; //empty statement so I can close the scope and declare variables.
    
    //UPDATE AND CHECK BALANCE FACTOR (HEIGHT)        
    struct node** balanced_tree     = head; 
    struct node** unbalanced_node   = NULL;  
    do{
        (*balanced_tree)->height = calc_height(*balanced_tree);
        int child_balance     = abs(calc_height((*balanced_tree)->right)-calc_height((*balanced_tree)->left));
        if(child_balance>1){    //tree is not balanced at this node
            unbalanced_node = balanced_tree;      
        }
        balanced_tree = ((*balanced_tree)->data > target_value) ? &(*balanced_tree)->left : &(*balanced_tree)->right;
        
    }while((*balanced_tree) != NULL);

    if(unbalanced_node) rebalance(unbalanced_node);     //will send closest unbalanced node (+-2) from the bottom up.

    return;
}

void rebalance(struct node **node){

    if(!node||!(*node)) return;    

    //VARs
    int balance_factor;
    struct node *sub_node;


    balance_factor = calc_height((*node)->right)-calc_height((*node)->left);

    if(balance_factor==-2){                                                 //LEFT subtree unbalanced
        
        sub_node        = (*node)->left;
        balance_factor  = calc_height(sub_node->right)-calc_height(sub_node->left);       
    
        if(balance_factor==-1||balance_factor==0){                          //left-left insert  -> single rotation.
            rotate_left_child(node);
        }else{                                                              //left-right insert -> double rotation.
            //bf must be 1
            double_left_child(node);
        }
    }else{                                                                  //RIGHT subtree unbalanced
    //bf must be 2

        sub_node = (*node)->right;
        balance_factor  = calc_height(sub_node->right)-calc_height(sub_node->left); 
        
        if(balance_factor==1||balance_factor==0){                           //right-right insert    -> single rotation.
            rotate_right_child(node);
        }else{                                                              //right-left insert     -> double rotation.  
        //bf must be -1
            double_right_child(node);
        }
    }
    
    return;
}

void rotate_left_child(struct node **node){
    //we rotate the node and its children clockwise.

    if(!node||!(*node)) return;

    struct node *child  = *node;
    struct node *rotational = (*node)->left;

    child->left  = rotational->right;
    //child->right = NULL;
    *node = rotational;
    (*node)->right = child;
    
    return;
}

void rotate_right_child(struct node **node){
    //we rotate the node and its children anti-clockwise.

    if(!node||!(*node)) return;

    struct node *child  = *node;
    struct node *rotational = (*node)->right;

    //child->left  = NULL;
    child->right = rotational->left;    //el rotational left!!
    *node = rotational;
    (*node)->left = child;
    
    return;
}

void double_left_child(struct node **node){
    //left then right
    rotate_right_child(&(*node)->left);
    rotate_left_child(node);
    return;
}

void double_right_child(struct node **node){
    //right then left
    rotate_left_child(&(*node)->right);
    rotate_right_child(node);
    return;
}

int calc_height(struct node *node){

    if(!node)   return -1;

    int left_branch     = calc_height(node->left) + 1;
    int right_branch    = calc_height(node->right) + 1;

    node->height = (left_branch > right_branch) ? left_branch : right_branch;
    return (left_branch > right_branch) ? left_branch : right_branch;
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
