#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef struct Stack{
    int top;
    char *array;
} Stack;

Stack *genStack(){
    Stack *S=(Stack*)malloc(sizeof(Stack));
    assert(S!=NULL);
    S->top=-1;
    S->array=(char*)malloc(sizeof(char)*30000000);
    return S;
}

void Push(Stack *S,char m){
    S->array[++S->top]=m;
}


int main(void){
    char player[2][10];
    int playerIndex=0;
    scanf("%s%s",player[0],player[1]);

    char *N=(char*)malloc(sizeof(char)*30000000),*M=(char*)malloc(sizeof(char)*30000000);
    scanf("%s%s",N,M);


    int coverage=0,pushSize=0;

    Stack *tempM=genStack();
    Push(tempM,M[pushSize]);

    char *ptr=strstr(N,tempM->array);
    coverage++;
    if(strlen(tempM->array)==strlen(M) && ptr!=NULL){//第一次就找到
            coverage%=1000000007;
            printf("%s\n%d\n",player[playerIndex],coverage);
    }else{


    while(1){

        if(strlen(tempM->array)==strlen(M)){
            coverage%=1000000007;
            printf("%s\n%d\n",player[playerIndex],coverage);
            break;
        }

        if(&ptr[1]==NULL)//檢查是否找到最後一位
            ptr=NULL;
        else
            ptr=strstr(&ptr[1],tempM->array);
        
        if(ptr==NULL){
            
            pushSize++;
            Push(tempM,M[pushSize]);
            ptr=strstr(N,tempM->array);
            coverage+=strlen(tempM->array);
            playerIndex++;
            playerIndex&=1;
            
        }
        else{
            coverage+=strlen(tempM->array);
            playerIndex++;
            playerIndex&=1;
        }
     
    }
    }
    
    return 0;
}
