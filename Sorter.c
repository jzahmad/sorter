#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void *sorter(void *p);
void *merger(void *p);
void swap(int* xp, int* yp);

typedef struct{
    int* list;
    int size;
}sortStruct;

typedef struct{
    sortStruct* merge1;
    sortStruct* merge2;
    int* finalMergeList;
}mergeStruct;

int main(int argc,const char* argv[]) {
    /*
    *It this part we will read the text file and put the integers in an array
    */
    int *list1 = malloc(500 * sizeof(int));
    int count = 0;
    FILE *file;
    file = fopen("IntegerList.txt", "r");
    if (file != NULL) {
        char buffer[1024];
        char *token;
        
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            token = strtok(buffer, ",");
            while (token != NULL) {
                int num = atoi(token);
                list1[count] = num;
                count++;
                token = strtok(NULL, ",");
            }
        }
        fclose(file);
    }
    /*
     * Now we will split it into two sublists and make repsective structs of those
     */
    int size1=count/2;
    int size2=count-size1;
    int *subList1 = malloc(size1 * sizeof(int));
    int *subList2 = malloc(size2 * sizeof(int));
    
    for(int i=0;i<size1;i++){
        subList1[i]=list1[i];
    }
    for(int i=size1;i<count;i++){
        subList2[i-size1]=list1[i];
    }
    sortStruct* p1=malloc(sizeof(sortStruct));
    p1->list=subList1;
    p1->size=size1;
    sortStruct* p2=malloc(sizeof(sortStruct));
    p2->list=subList2;
    p2->size=size2;
    
    /*
    *Let's make threads with that data
    */
    pthread_t s1;
    pthread_t s2;
    pthread_t m1;
    int *merList = malloc(count * sizeof(int));
    
    // creating the sorting threads
    pthread_create(&s1, NULL, sorter, p1);
    pthread_create(&s2, NULL, sorter, p2);
    
    // wait for them to finish
    pthread_join(s1,NULL);
    pthread_join(s2,NULL);
    
    // create the merging thread
    mergeStruct* m=malloc(sizeof(mergeStruct));
    m->merge1=p1;
    m->merge2=p2;
    m->finalMergeList=merList;
    pthread_create(&m1, NULL, merger,m);
    
    //wait for them to finish
    pthread_join(m1,NULL);
    
    // now we will generate output file
    FILE *output;
    output = fopen("SortedIntegerList.txt", "w");
    for (int i = 0; i < count; i++) {
        if (i != 0) {
            fprintf(output, ",");
        }
        fprintf(output, "%d", m->finalMergeList[i]);
    }
    fprintf(output,"\n");
    fclose(output);
    return 0;
}
/*
* This is the sorting function where I used the bubble sort algorithm.
*/
void *sorter(void* p){
    int i, j;
    sortStruct* params = p;
    int *arr = params->list;
    int n =params->size;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}
/*
* This is the merging algorithm.
*/
void *merger(void *p){
    
    mergeStruct* para = p;
    
    sortStruct* params1 = para->merge1;
    sortStruct* params2 = para->merge2;
    
    int *A=params1->list;
    int *B=params2->list;

    int  m=params1->size;
    int  n=params2->size;

    int* C = malloc((m + n) * sizeof(int));
    C=para->finalMergeList;

    // merging part
    int i = 0, j = 0, k = 0;
    while (i < m && j < n) {
        if (A[i] <= B[j]) {
            C[k] = A[i];
            i++;
        } else {
            C[k] = B[j];
            j++;
        }
        k++;
    }

    while (i < m) {
        C[k] = A[i];
        i++;
        k++;
    }

    while (j < n) {
        C[k] = B[j];
        j++;
        k++;
    }

    return C;
}
/*
* This is the swap function for sorting.
*/
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
