#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "akihabara.h"
#pragma GCC optimize("O3,Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

long long int hashSize = 16777216;//mod多少
typedef struct node{
    long long int key;
    struct node *next;
    int count;
}Node;
Node storage[16777216];
Node *nextNode = &storage[0];

Node *getNode(){
    Node *N = (Node*)malloc(sizeof(Node));
    assert(N!=NULL);
    N->count = 0;
    N->next = NULL;
    return N;
}

void hash(Node **Hash, long long int key){
    long long int hashValue = key&(hashSize-1);
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

void init(Node **Hash, long long int size){
    for(int i=0;i<size;i++){
        Hash[i] = nextNode;
        nextNode++;
        Hash[i]->count = 0;
        Hash[i]->next = NULL;
    }
    // printf("test");
}

int findTargetCount(Node **Hash, long long int target){
    long long int hashValue = target&(hashSize-1);
    Node *temp = Hash[hashValue];
    if(temp->count == 0){//這格是空的
        return 0;
    }
    else{//這格至少有一個東西
        while(temp && (temp->key != target))
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

    long long int count=0;
    long long int *Sum=(long long int*)malloc(sizeof(long long int)*N);
    Node **Hash=(Node**)malloc(sizeof(Node*)*hashSize);
    init(Hash,hashSize);
    Sum[0]=Array[0];
    for(int i=1;i<N;i++){
        Sum[i] = Sum[i-1] + Array[i];
    }

    for(int i=0;i<N;i++){
        long long int target = Sum[i]-K;
        if(target == 0)
            ++count;
        count+=findTargetCount(Hash,target);
        hash(Hash,Sum[i]);

    }

    printf("%lld\n",count);

    return 0;
}