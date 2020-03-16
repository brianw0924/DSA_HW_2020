#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef struct queue{
    int front;
    int rear;
    char *array;
} Queue;

Queue *genQueue(){
    Queue *Q=(Queue*)malloc(sizeof(Queue));
    assert(Q!=NULL);
    Q->front=-1;
    Q->rear=0;
    Q->array=(char*)malloc(sizeof(char)*30000000);
    return Q;
}

void Push(Queue *Q,char m){
    Q->array[++Q->front]=m;
}


int main(void){
    char player[2][10];
    int playerIndex;
    scanf("%s%s",player[0],player[1]);

    char *N=(char*)malloc(sizeof(char)*30000000),*M=(char*)malloc(sizeof(char)*30000000);
    scanf("%s%s",N,M);


    int coverage=0,pushSize=0;

    Queue *tempM=genQueue();
    Push(tempM,M[pushSize]);

    char *ptr=strstr(N,tempM->array);
    coverage++;

    while(1){
        if(ptr+1==NULL)
            ptr=NULL;
        else
            ptr=strstr(++ptr,tempM->array);
        
        if(ptr==NULL){
            pushSize++;
            Push(tempM,M[pushSize]);
            ptr=strstr(N,tempM->array);
        }
        playerIndex++;
        playerIndex%=2;
        coverage+=strlen(tempM->array);
        
        if(strlen(tempM->array)==strlen(M)){
            printf("%s\n%d\n",player[playerIndex],coverage);
            break;
        }
    }





    return 0;
}
