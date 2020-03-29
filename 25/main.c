#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>


typedef struct doublelinklist{
    char letter;
    struct doublelinklist *prev;
    struct doublelinklist *next;
} DoubleLL;

typedef struct {
    struct doublelinklist *head;
    struct doublelinklist *tail;
    struct doublelinklist *cursor;
} Info;

Info *genInfo(){
    Info *I=(Info*)malloc(sizeof(Info));
    I->head=NULL;
    I->tail=NULL;
    I->cursor=NULL;
    return I;
}

/*typedef struct{
    DoubleLL *info->head;
    DoubleLL *info->tail;
    DoubleLL *info->cursor;
} text;

text genText(){
    text T;
    T.info->head=NULL;
    T.info->tail=NULL;
    T.info->cursor=NULL;
    return text;
}*/



DoubleLL *genDoubleLL(char letter){
    DoubleLL *DLL = (DoubleLL*)malloc(sizeof(DoubleLL));
    DLL->letter=letter;
    DLL->prev=NULL;
    DLL->next=NULL;
    return DLL;
}

DoubleLL *Insert(DoubleLL *new , Info *info){

    if(info->tail==NULL && info->head==NULL && info->cursor==NULL){//text全空
        info->head=new;
        info->tail=new;
        info->cursor=new;
    }else if(info->cursor==NULL){//text有東西,info->cursor在最頭
        new->next=info->head;
        info->head->prev=new;
        info->head=new;
        info->cursor=new;
    }else if(info->cursor==info->tail){//text有東西,info->cursor在最尾
        info->tail->next=new;
        new->prev=info->tail;
        info->tail=new;
        info->cursor=new;
    }else{//text有東西,info->cursor在中間

    DoubleLL *temp;
    temp=info->cursor->next;//把下一個存起來
    info->cursor->next=new;//插入
    new->next=temp;
    new->prev=info->cursor;
    info->cursor=new;
    }

    return info->head;
}



/*typedef struct{
    int top;
    int info->cursor;
    DoubleLL *info->head;
} Stack;

Stack *genStack(){
    Stack *S=(Stack*)malloc(sizeof(Stack));
    S->front=-1;
    S->rear=0;
    S->info->head=NULL;
}*/

int main(void){
    int T;
    Info *info=genInfo();//info->cursor=NULL等同於在最前面
    scanf("%d",&T);
    char *str=(char*)malloc(sizeof(char)*1000000);
    int letter;

    
    
    for(int i=0;i<T;i++){
        scanf("%s",str);

        int j=0;
        while(str[j]!='\0'){

            letter=(int)str[j];

            if (islower(letter)){
                DoubleLL *new=genDoubleLL(str[j]);
                info->head=Insert(new,info);  
            }else{

                switch (str[j]){
                    case 'H':
                        if(info->cursor!=NULL){
                            if(info->cursor==info->head)
                                info->cursor=NULL;
                            else
                                info->cursor=info->cursor->prev;
                        }
                        break;
                    case 'L':
                        if(info->cursor!=NULL){
                            if(info->cursor!=info->tail)
                                info->cursor=info->cursor->next;
                        }
                        break;
                    case 'I':
                    case 'A':
                    case 'V':
                    case 'D':
                    case 'R':
                    default:
                    break;
                }
            }
            j++;
        }

        DoubleLL *temp=info->head;
        while(temp!=NULL){
            printf("%c",temp->letter);
            temp=temp->next;
        }
        printf("\n");
        info=genInfo();

    }
    


    return 0;
}