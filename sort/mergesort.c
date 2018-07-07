//MERGE SORT IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 10

//DECLARATION
void merge(int* arr, int* tmp, int left, int center, int right);
int* mergeSort(int *arr, int length);
void doMergeSort(int *arr, int *tmp, int left, int right);

int main(){

    int i;
    int arr[N] = {6,9,2,4,1,8,3,7,5,0};
    int* sorted;

    for(i=0; i<N;i++)  printf("Element %d:\t%d\n",i,arr[i]);
    printf("---------------\n");
    sorted = mergeSort(arr,N);
    for(i=0; i<N;i++)  printf("Element %d:\t%d\n",i,sorted[i]);
    free(sorted);

    return 0;
}

int* mergeSort(int *arr, int length) {
    int *tmp = (int*)malloc(sizeof(int) * length);
    doMergeSort(arr, tmp, 0, length - 1);
    return tmp;
}

void doMergeSort(int *arr, int *tmp, int left, int right) {
  if(left < right) {
    int center = (left + right) / 2;
    doMergeSort(arr, tmp, left, center);
    doMergeSort(arr, tmp, center + 1, right);
    merge(arr, tmp, left, center + 1, right);
  }
}

void merge(int* arr, int* tmp, int left, int center, int right){
  
    printf("merge: (left)>%d\t(center)>%d\t(right)>%d\n",left,center,right);

    int a,b,i;
    int* copy;
    bool counter_stop_a, counter_stop_b, merge, dif;


    //DIFF BETWEEN SORTING DIRECTLY FROM ARRAY AND MERGING TWO PREV SORTED ARRs
    a     = left;
    b     = center;
    merge = (right-left)>1;
    dif   = (center==right);   

    copy = (int*)malloc(sizeof(int)*(right+1));
    for(i=left; i<=right; i++){
        if((i==right)&&dif){
            copy[i] = arr[i];
        }else{
            copy[i] = (merge) ? tmp[i] : arr[i];
        }
    }    
    
    for(i=left;i<=right;i++){
             
        counter_stop_a = !(a<center);
        counter_stop_b = (b>right);
   
        if((copy[a]<copy[b]&&(!counter_stop_a))||counter_stop_b){
            tmp[i] = copy[a];
            a++;
        }else if(!counter_stop_b){
            tmp[i] = copy[b];
            b++;
        }
    }
    free(copy);
}
