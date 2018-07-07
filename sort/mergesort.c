//MERGE SORT IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define N 10

//DECLARATION
void merge(int* arr, int* tmp, int left, int center, int right);
int* mergeSort(int *arr, int length);
void doMergeSort(int *arr, int *tmp, int left, int right);
void testSort(int* arr, int length);

int main(){

    //VARs
    int random_arr[N];
    int single_arr[1];
    int same_arr[N];
    int* empty_arr;


    srand(time(NULL));
    
    //DEF
    single_arr[0] = rand()%100;
    empty_arr     = NULL;
    for(int i=0; i<N; i++){
        
        same_arr[i]     = single_arr[0];
        random_arr[i]   = rand()%100;
    }

    //TEST
    testSort(random_arr,N);    
    testSort(same_arr,N);    
    testSort(empty_arr,N);    
    testSort(single_arr,1);    

    return 0;
}

int* mergeSort(int *arr, int length) {
    
    if(!arr)    return NULL;

    int *tmp = (int*)malloc(sizeof(int) * length);
    doMergeSort(arr, tmp, 0, length - 1);
    return tmp;
}

void doMergeSort(int *arr, int *tmp, int left, int right) {
  
    if(right==0)    tmp[0] = arr[0];

    if(left < right) {
        int center = (left + right) / 2;
        doMergeSort(arr, tmp, left, center);
        doMergeSort(arr, tmp, center + 1, right);
        merge(arr, tmp, left, center + 1, right);
    }
}

void merge(int* arr, int* tmp, int left, int center, int right){
  
    /*  DEBUG
    printf("merge: (left)>%d\t(center)>%d\t(right)>%d\n",left,center,right);
    */

    //VARs
    int a,b;                                    //counters for halves arrays
    bool ctr_stop_a, ctr_stop_b;                //boolean counter stops
    //AUXILIARY
    int* copy,i;
    bool merge, dif;
   
    //DEF
    a     = left;
    b     = center;
    merge = (right-left)>1;
    dif   = (center==right);   

    //DIFF BETWEEN SORTING DIRECTLY FROM INPUT ARRAY AND MERGING TWO PREV SORTED ARR FROM TMP
    copy = (int*)malloc(sizeof(int)*(right+1));
    for(i=left; i<=right; i++){
        if((i==right)&&dif){
            copy[i] = arr[i];
        }else{
            copy[i] = (merge) ? tmp[i] : arr[i];
        }
    }    
    //ACTUAL SORTING
    for(i=left;i<=right;i++){
             
        ctr_stop_a = !(a<center);
        ctr_stop_b = (b>right);
   
        if((copy[a]<copy[b]&&(!ctr_stop_a))||ctr_stop_b){
            tmp[i] = copy[a];
            a++;
        }else{       
            tmp[i] = copy[b];
            b++;
        }
    }

    free(copy);
    return;
}


void testSort(int* arr, int length){
    
    int* sorted, i;
    
    printf("****I N P U T   A R R A Y****\n");
    if(!arr){
        printf("Empty input array!\n");
    }else{
        for(i=0; i<length;i++)  printf("Element %d:\t%d\n",i+1,arr[i]);
    }
    printf("----S O R T E D----\n");
    if((sorted = mergeSort(arr,length)) != NULL){
        for(i=0; i<length;i++)  printf("Element %d:\t%d\n",i+1,sorted[i]);
        free(sorted);
    }else{
        printf("Empty output array!\n");
    }

    return;
}
