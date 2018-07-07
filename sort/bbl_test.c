#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//DECLARATION
int* merge(int* arr, int length);
void testSort(int* arr, int length);

int main(int argc, char** argv){

    //VARs
    int len, number = 0;
    char *num;

    //CLA
    if(argc!=2) return -1;  //takes only one input value from CLA.
    num = argv[1];
    len = strlen(num);
    for(int i=0; i<len;i++) number = number*10 + (num[i]-'0');
    //RND
    if(number>0){
        printf("CREATING RANDOM ARRAY OF N: %d\n",number);
        int random_arr[number];        
        //DEF
        srand(time(NULL));
        for(int i=0; i<number; i++)  random_arr[i]   = rand()%100;
        //TEST
        testSort(random_arr,number);
    }
    return 0;
}

void testSort(int* arr, int length){

    int* sorted, i;

    printf("****I N P U T   A R R A Y****\n");
    if(!arr||length==0){
        printf("Empty input array!\n");
    }else{
        for(i=0; i<length;i++)  printf("Element %d:\t%d\n",i+1,arr[i]);
    }
    printf("----S O R T E D----\n");
    if((sorted = merge(arr, length)) != NULL){
        for(i=0; i<length;i++)  printf("Element %d:\t%d\n",i+1,sorted[i]);
    }else{
        printf("Empty output array!\n");
    }

    return;
}


int* merge(int* arr, int length){

    //BUBBLE SORT O(N^2)
    int cont1, cont2;
    if(!arr||length==0) return NULL;    

    cont1 = 0;
    while(cont1 < length){
        cont2 = cont1 + 1;
        while(cont2 < length){
            if (arr[cont1] > arr[cont2]){
                //swap
                int temp;
                temp = arr[cont1];
                arr[cont1] = arr[cont2];
                arr[cont2] = temp;
            }
            cont2++;
        }
        cont1++;
    }
    return arr;
}
