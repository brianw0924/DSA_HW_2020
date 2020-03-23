#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct{
    int sth;
    int rng;
    int left;
    int right;
} Stand;

Stand *genStand(int sth){
    Stand *S=(Stand*)malloc(sizeof(Stand));
    assert(S!=NULL);
    S->sth=sth;
    return S;
}

typedef struct{
    int top;
    int *index;
} Stack;



Stack *genStack(int N){
    Stack *S=(Stack*)malloc(sizeof(Stack));
    assert(S!=NULL);
    S->top=-1;
    S->index=(int*)malloc(sizeof(int)*N);
    return S;
}

void Push(Stack *S , int index){
    S->index[++S->top]=index;
}

int Pop(Stack *S){
    return S->index[S->top--];
}





int main(void){
    int N,sth;
    scanf("%d",&N);
    Stand **stand=(Stand**)malloc(sizeof(Stand*)*N);
    for(int i=0; i<N ; i++){
        //scanf("%d",&(stand[i].sth));
        scanf("%d",&sth);
        stand[i]=genStand(sth);
    }
    for(int i=0; i<N ; i++){
        scanf("%d",&(stand[i]->rng));
    }
    
    
     Stack *stack=genStack(N);//stack裡面存放index
     int temp;
     /*for(int i=0;i<N;i++){
        //printf("%d\n",i);

        if(stack->top == -1){
             stand[i]->left=0;
             }
        else{
            stand[i]->left=i;
            //把打得到的Pop光
            while(stack->top != -1 && stand[stack->index[stack->top]]->sth <= stand[i]->sth){
                temp=Pop(stack);
                stand[temp]->right=i-1;
                if(stand[i]->sth != stand[temp]->sth)
                    stand[i]->left=stand[temp]->left;
                }

            while( (stand[temp]->sth != stand[i]->sth) &&
                (stand[temp]->left - 1>=0) && 
                (stand[stand[temp]->left - 1]->sth < stand[i]->sth) ){
                stand[i]->left = (stand[temp]->left) -1 ;
                temp=stand[i]->left;
            }
        }
        

        Push(stack,i);
        //printf("%d\n",i);
     }*/

     for(int i=0;i<N;i++){

        if(stack->top == -1){
             stand[i]->left=0;
             }
        else{
            //把打得到的Pop光
            while(stack->top != -1 && stand[stack->index[stack->top]]->sth <= stand[i]->sth){
                temp=Pop(stack);
                stand[temp]->right=i-1;
            }
        }
        Push(stack,i);
     }

     while(stack->top!=-1){
         temp=Pop(stack);
         stand[temp]->right=N-1;
     }

    /*for(int i=0;i<N;i++){
        printf("right=%d\n",stand[i]->right);
    }*/

    stack->top=-1;

     for(int i=N-1;i>=0;i--){

        if(stack->top == -1){
             stand[i]->right=N-1;
             }
        else{
            //把打得到的Pop光
            while(stack->top != -1 && stand[stack->index[stack->top]]->sth <= stand[i]->sth){
                temp=Pop(stack);
                stand[temp]->left=i+1;
            }
        }
        Push(stack,i);
     }

     while(stack->top!=-1){
         temp=Pop(stack);
         stand[temp]->left=0;
     }

     /*for(int i=0;i<N;i++){
        printf("left=%d\n",stand[i]->left);
    }*/

    for(int i=0;i<N;i++){
        printf("%d %d\n",stand[i]->left ,stand[i]->right);
    }
    return 0;
}
