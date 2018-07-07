//MERGE SORT IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//DECLARATION
void merge(int* arr, int* tmp, int left, int center, int right);
int* mergeSort(int *arr, int length);
void doMergeSort(int *arr, int *tmp, int left, int right);
void testSort(int* arr, int length);

int main(int argc, char** argv){

    //VARs
    int* random_arr = NULL, len, number = 0;
    char *num;

    //CLA
    if(argc!=2) return -1;  //takes only one input value from CLA.
    num = argv[1];
    len = strlen(num);
    for(int i=0; i<len;i++) number = number*10 + (num[i]-'0');
    //RND
    if(number>0){
        printf("CREATING RANDOM ARRAY OF N: %d\n",number);
        random_arr = (int*)malloc(sizeof(int)*number);
    }
    //DEF
    srand(time(NULL));
    for(int i=0; i<number; i++)  random_arr[i]   = rand()%100;
    
    //TEST
    testSort(random_arr,number);    
    free(random_arr);

    return 0;
}

int* mergeSort(int *arr, int length) {
    
    if(!arr||length==0)    return NULL;

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
