#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void merge(int *arr, int *tmp, int left, int right, int end);
int *mergeSort(int *arr, int length);
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

int * mergeSort(int *arr, int length) {
    if(!arr || length == 0) return NULL;
    int *tmp = (int*)malloc(sizeof(int) * length);
    if(length == 1){
        *tmp = *arr;
        return tmp;
    }
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

void merge(int *arr, int *tmp, int left, int right, int end){
        int *aArr = (int *)malloc(sizeof(int)*(right-left));
        int *bArr = (int *)malloc(sizeof(int)*(end-right+1));
        int aCtr = 0;
        int bCtr = 0;
        for(int i = 0;i < right-left;i++){
        if(right-left == 1){// if this element is being put into tmp for the first time, take from arr
            *(aArr+i) = *(arr+left+i);
        }else{
                    *(aArr+i) = *(tmp+left+i);
        }
        }
        for(int i = 0;i < end-right+1;i++){
                if(end-right == 0){// if this element is being put into tmp for the first time, take from arr
            *(bArr+i) = *(arr+right+i);
        }else{
            *(bArr+i) = *(tmp+right+i);
        }
        }
        while(aCtr+bCtr<end-left+1){
                if(aCtr == right-left){
                        *(tmp+left+aCtr+bCtr) = *(bArr+bCtr);
                        bCtr++;
                }else if(bCtr == end-right+1){
                        *(tmp+left+aCtr+bCtr) = *(aArr+aCtr);
                        aCtr++;
                }else if(*(aArr+aCtr)>*(bArr+bCtr)){
                        *(tmp+left+aCtr+bCtr) = *(bArr+bCtr);
                        bCtr++;
                }else{
                        *(tmp+left+aCtr+bCtr) = *(aArr+aCtr);
                        aCtr++;
                }
        }
        free(aArr);
        free(bArr);
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
