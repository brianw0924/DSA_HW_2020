#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "akihabara.h"


int hashSize = 1000000;//mod多少

typedef struct node{
    long long int key;
    int count;
    struct node *next;
}Node;

Node *getNode(){
    Node *N=(Node*)malloc(sizeof(Node));
    assert(N!=NULL);
    N->count = 0;
    N->next = NULL;
    return N;
}

void hash(Node **Hash, int key){
    int hashValue=key%hashSize;
    Node *temp = Hash[hashValue];
    if(temp->count == 0){//空櫃子
        temp->count++;
        temp->key = key;
    }else{//Chaining
        Node *prev=temp;
        while(temp && (temp->key != key)){
            prev = temp;
            temp = temp->next;
        }
        if(temp == NULL){
            prev->next = getNode();
            temp = prev->next;
            temp->key = key;
            temp->count++;
        }else{
            temp->count++;
        }
    }
}

void init(Node **Hash, int size){
    for(int i=0;i<size;i++){
        Hash[i] = getNode();
    }
}

int findTargetCount(Node **Hash, int target){
    int hashValue = target%hashSize;
    Node *temp = Hash[hashValue];
    if(temp->count == 0){
        // printf("test1\n");
        return 0;
    }
    else{
        while(temp->key != target)
            temp = temp->next;
        if(temp == NULL)
            return 0;
        else
            return temp->count;
    }
}



int Array[50000000];
int main(){
    unsigned int N = getN();
    long long int K = getK();
    getArray(N, Array);

    int count=0;
    long long int *Sum=(long long int*)malloc(sizeof(long long int)*N);
    Node **negative_Hash=(Node**)malloc(sizeof(Node*)*hashSize);
    Node **positive_Hash=(Node**)malloc(sizeof(Node*)*hashSize);
    init(negative_Hash, hashSize);
    init(positive_Hash, hashSize);
    Sum[0]=Array[0];
    for(int i=1;i<N;i++){
        Sum[i] = Sum[i-1] + Array[i];
    }


    for(int i=0;i<N;i++){
        int target = Sum[i]-K;

        //找區間和=K
        if(target<0){
            target = -target;
            count+=findTargetCount(negative_Hash,target);
        }else if(target == 0){
            count++;
            count+=findTargetCount(positive_Hash,target);
        }else
            count+=findTargetCount(positive_Hash,target);


        //處理key,Hash
        if(Sum[i]<0){
            int temp = -Sum[i];
            hash(negative_Hash, temp);
        }else{//Sum[i]>=0
            hash(positive_Hash, Sum[i]);
        }

    }

    printf("%d\n",count);

    return 0;
}