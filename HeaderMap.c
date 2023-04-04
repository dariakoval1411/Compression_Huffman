#include <stdlib.h>
#include "HeaderMap.h"

header * createHeader(int capacity){
    header *tmp=malloc(sizeof(header));

    if(tmp==NULL){
        return NULL;
    }

    tmp->name=malloc(sizeof(char *) * capacity);

    if(tmp->name==NULL)
        return NULL;
    
    tmp->capacity=capacity;
    tmp->size=0;

    return tmp;
}

int double_header_capacity(header *arr){
    arr->capacity *=2;
    arr->name=realloc(arr->name,sizeof(char*) * arr->capacity);

    if(arr->name==NULL)
        return 1;
    
    return 0;
}

int add_header(header *arr,char *word){
    
    if(arr->size >= arr->capacity)
        if(double_header_capacity(arr)==1)
            return 1;
    
    arr->name[arr->size++]=word;

    return 0;
}

void free_header(header *arr){
    free(arr->name);
    free(arr);
}
