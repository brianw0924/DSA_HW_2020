#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdbool.h>
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


DoubleLL *genDoubleLL(char letter){
    DoubleLL *DLL = (DoubleLL*)malloc(sizeof(DoubleLL));
    DLL->letter=letter;
    DLL->prev=NULL;
    DLL->next=NULL;
    return DLL;
}

Info *Insert(DoubleLL *new , Info *info){

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
        new->prev=info->tail;
        info->tail->next=new;
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

    return info;
}

Info *Overwrite(DoubleLL *new , DoubleLL *selectStart , Info *info , int select){
    if(select>0){//selectStart -> new -> cursor的next
        new->next = info->cursor->next;
        new->next->prev = new;
        selectStart->next = new;
        new->prev = selectStart;
    }else if(select<0){//cursor -> new -> selectStart的next
        new->next = selectStart->next;
        new->next->prev = new;
        info->cursor->next = new;
        new->prev = info->cursor;
    }

    return info;
}

int main(void){
    int T;
    Info *info=genInfo();//head,tail,cursor
    scanf("%d",&T);
    char *str=(char*)malloc(sizeof(char)*1000000);
    int letter,select;
    DoubleLL *selectStart=NULL;
    bool selectionMode=0;

    
    
    for(int i=0;i<T;i++){
        scanf("%s",str);

        int j=0;
        while(str[j]!='\0'){

            letter=(int)str[j];

            if (islower(letter)){//a~z
                DoubleLL *new=genDoubleLL(str[j]);

                if(selectionMode){
                    info=Overwrite(new,selectStart,info,select);
                    selectionMode=!selectionMode;//exit selectionMode
                    select=0;//判斷select方向歸零
                }else{
                    info=Insert(new,info);  
                }

            }else{//指令

                switch (str[j]){

                    case 'H'://左移
                        if(selectionMode)
                            select--;//選取模式往左

                        if(info->cursor!=NULL){
                            
                            if(info->cursor==info->head)//已經在最頭
                                info->cursor=NULL;
                            else
                                info->cursor=info->cursor->prev;
                        }
                        break;

                    case 'L'://右移
                        if(selectionMode)
                            select++;//選取模式往右


                        if(info->head!=NULL){
                            if(info->cursor==NULL)//已經在最頭
                                info->cursor = info->head;
                            else if(info->cursor!=info->tail)//不在最尾
                                info->cursor=info->cursor->next;
                        }
                        break;

                    case 'I'://移到最頭
                        info->cursor=NULL;
                        break;

                    case 'A'://移到最尾
                        info->cursor=info->tail;
                        break;

                    case 'V'://SelectionMode
                        if(selectionMode)//原本已經selectionMode,現在要關掉
                            selectStart=NULL;
                        else{//原本不在selectionMode,現在要進入
                            selectStart=info->cursor;
                            select=0;//紀錄選取的方向
                        }
                        selectionMode=!selectionMode;
                        break;

                    case 'D'://Delete
                        /*if(select){
                            info=Delete();
                            selectionMode=!selectionMode;
                        }
                        break;*/
                    case 'R'://Reverse
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