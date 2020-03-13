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

int StackEmpty(Stack *stack){
    return (stack->top == -1);
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
    //printf("%lu\n",strlen(num));
    while(i<strlen(num)){//還沒放完stack就繼續跑
        if(S->top==-1){//第一次
            Push(S,num[i++]);
            //printf("(Push)stacktop=%c\n",S->array[S->top]);
        }
        else if(num[i] < S->array[S->top] && (num[i]!='0' || S->top!=0)){//當前數字比stack頂還小

            while(num[i] < S->array[S->top] && (num[i]!='0' || S->top!=0) && (!StackEmpty(S)) &&(k!=0)){
                Pop(S);
                //printf("(Pop)stacktop=%c\n",S->array[S->top]);
                k--;
            }
            
            Push(S,num[i++]);
            //printf("(Push)stacktop=%c\n",S->array[S->top]);
        }else{
            Push(S,num[i++]);
            //printf("(Push)stacktop=%c\n",S->array[S->top]);
        }
        
        
    }
    //printf("i=%d\n",i);
    i--;
    //printf("%d\n",k);

    while(k!=0){
            Pop(S);
            //printf("k=%d\n",k);
            k--;
            i--;
        }
    
    
    while(S->start<=S->top){
        printf("%c",S->array[S->start++]);
    }

    free(num);
    free(S->array);
    
    return 0;
}
