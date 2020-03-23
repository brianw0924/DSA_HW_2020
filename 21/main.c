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
        scanf("%d",&sth);
        stand[i]=genStand(sth);
    }
    for(int i=0; i<N ; i++){
        scanf("%d",&(stand[i]->rng));
    }
    
    
     Stack *stack=genStack(N);//stack裡面存放index
     int temp,d;
     
     for(int i=0;i<N;i++){//從左邊找right
        
            //把打得到的Pop光
        while(stack->top != -1 && stand[stack->index[stack->top]]->sth <= stand[i]->sth){
            temp=Pop(stack);//temp是index
            d=stand[temp]->rng - (i-1-temp);
            if(d>=0)
                stand[temp]->right=i-1;
            else
                stand[temp]->right=temp+stand[temp]->rng;
        }
        
        Push(stack,i);
     }

     while(stack->top!=-1){
        temp=Pop(stack);
        if(stand[temp]->rng < (N-1-temp))
            stand[temp]->right=temp+stand[temp]->rng;
        else
            stand[temp]->right=N-1;
     }

    /*for(int i=0;i<N;i++){
        printf("right=%d\n",stand[i]->right);
    }*/

    stack->top=-1;

     for(int i=N-1;i>=0;i--){//從右邊找left
        
        //把打得到的Pop光
        while(stack->top != -1 && stand[stack->index[stack->top]]->sth <= stand[i]->sth){
            temp=Pop(stack);
            d=stand[temp]->rng - (temp-(i+1));
            if(d>=0)
                stand[temp]->left=i+1;
            else
                stand[temp]->left=temp-stand[temp]->rng;

        }
        
        Push(stack,i);
     }

     while(stack->top!=-1){
        temp=Pop(stack);
        if(stand[temp]->rng<temp)
            stand[temp]->left=temp-stand[temp]->rng;
        else
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
