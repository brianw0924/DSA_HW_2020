#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct stack{
    int top;
    int start;
    char *array;
} Stack;

char Pop(Stack *stack){
    return(stack->array[stack->top--]);
}

void Print(Stack *stack){
    printf("%c",stack->array[stack->start++]);
}

void Push(Stack *stack , char digit){
    stack->array[++(stack->top)]=digit;
}



int main(void){
    int k,ans=0;
    char *num=(char*)malloc(sizeof(char)*100000000);
    scanf("%s%d",num,&k);
    
    Stack *S=(Stack*)malloc(sizeof(Stack));
    S->top=-1;
    S->start=0;
    S->array=(char*)malloc(sizeof(char)*100000000);
    
    int i=0;
    while(i<strlen(num)){//還沒放完stack就繼續跑
        if(S->top==-1)//第一次
            Push(S,num[i++]);

        else if(num[i] < S->array[S->top] && (num[i]!='0' || S->top!=0)){//當前數字比stack頂還小

            while(num[i] < S->array[S->top] && (num[i]!='0' || S->top!=0)){
                Pop(S);
                k--;
            }
            
            Push(S,num[i++]);
            
        }else
            Push(S,num[i++]);
            //printf("stacktop=%c\n",S->array[S->top]);
    }
    i--;

    if(k!=0)
        for(;k!=0;k--,i--)
            Pop(S);
    
    while(S->start<=S->top){
        Print(S);
    }


    
    return 0;
}
