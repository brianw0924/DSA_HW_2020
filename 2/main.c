#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct stack{
    int top;
    int start;
    char array[100000001];
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

char num[100000001];

int main(void){


    int k,Zero=-1;
    
    scanf("%s%d",num,&k);
    
    Stack *S=(Stack*)malloc(sizeof(Stack));
    S->top=-1;
    S->start=0;
    
    int i=0;
    while(num[i]!='\0'){
        /*printf("k=%d\n",k);
        printf("num=%c\n",num[i]);
        printf("stack=%s\n",S->array);
        printf("top=%d\n",S->top);*/

        if(StackEmpty(S)){//空的直接push
            Push(S,num[i++]);

        }else if(num[i] >= S->array[S->top]){

            if(num[i]!='0'){
                if((S->array[S->top]=='0') && (S->array[0] > num[i]) && ((S->top - S->start +1)<=k)){
                    k-=( (S->top) - (S->start) +1 );
                    S->top=-1;
                }
            }
            Push(S,num[i++]);

        }else{//num[i]比stack的top還"小"

            if(num[i]=='0'){
                while(num[i] < S->array[S->top] && k!=0 && S->top!=0){//Pop到底
                    Pop(S);
                    k--;
                }
                
            }else{//num!='0'
                while(num[i] < S->array[S->top] && k!=0){
                    Pop(S);
                    k--;
                }

                if((S->array[S->top]=='0') && (S->array[0] > num[i]) && ((S->top - S->start +1)<=k)){
                    k-=( (S->top) - (S->start) +1 );
                    S->top=-1;
                }
                
            }

            
        Push(S,num[i++]);
            }
    //printf("\n\n");
    }
        
        
    
    i--;

    while(k!=0){
            Pop(S);
            k--;
            i--;
        }
    S->array[++S->top]='\0';
    printf("%s\n",S->array);

    


    return 0;
}
