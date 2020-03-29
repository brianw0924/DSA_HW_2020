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

DoubleLL *genDoubleLL(char letter){
    DoubleLL *DLL = (DoubleLL*)malloc(sizeof(DoubleLL));
    DLL->letter=letter;
    DLL->prev=NULL;
    DLL->next=NULL;
    return DLL;
}

Info *genInfo(){
    Info *I=(Info*)malloc(sizeof(Info));
    DoubleLL *Begin = genDoubleLL('S');//最左邊設一個不存在的位置,方便cursor指
    I->head=Begin;
    I->tail=Begin;
    I->cursor=Begin;
    return I;
}

Info *Insert(DoubleLL *new , Info *info){

    if(info->cursor == info->tail){//cursor在最尾
        new->prev = info->tail;
        info->tail->next = new;
        info->tail = new;
        info->cursor = new;
    }else{
        new->prev = info->cursor;
        new->next = info->cursor->next;
        new->next->prev = new;
        info->cursor->next = new;
        info->cursor = new;
    }

    return info;
}

Info *Overwrite(DoubleLL *new , DoubleLL *selectStart , Info *info , int select){
    if(select>0){//selectStart -> new -> cursor的next
        selectStart->next = new;
        new->prev = selectStart;

        if(info->cursor != info->tail){
            new->next = info->cursor->next;
            new->next->prev = new;
        }else{
            info->tail = new;
        }
    }else if(select<0){//cursor -> new -> selectStart的next
        info->cursor->next = new;
        new->prev = info->cursor;

        if(selectStart != info->tail){
            new->next = selectStart->next;
            new->next->prev = new;
        }else{
            info->tail = new;
        }
        
    }

    info->cursor = new;


    return info;
}

Info *Delete(DoubleLL *selectStart , Info *info , int select){
    if(select>0){
        if(info->cursor == info->tail){
            selectStart->next = NULL;
            info->tail = selectStart;
        }else{
            selectStart->next = info->cursor->next;
            selectStart->next->prev = selectStart;
        }
        info->cursor = selectStart;

    }else if(select<0){
        if(selectStart == info->tail){
            info->cursor->next = NULL;
            info->tail = info->cursor;
        }else{
            info->cursor->next = selectStart->next;
            info->cursor->next->prev = info->cursor;
        }
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
    bool selectionMode=false;

    
    for(int i=0;i<T;i++){
        scanf("%s",str);

        int j=0;
        while(str[j]!='\0'){
            //printf("%c %d\n",str[j],select);
            letter=(int)str[j];

            if (islower(letter)){//a~z
                DoubleLL *new=genDoubleLL(str[j]);

                if(selectionMode){
                    if(select!=0)
                        info=Overwrite(new,selectStart,info,select);
                    else
                        info=Insert(new,info);  
                    selectionMode=!selectionMode;//exit selectionMode
                }else{
                    info=Insert(new,info);  
                }
            }else{//指令

                switch (str[j]){

                    case 'H'://左移

                        if(info->cursor->letter != 'S'){//不在最頭
                            info->cursor=info->cursor->prev;
                            if(selectionMode)
                                select--;//選取模式往左
                        }
                        break;

                    case 'L'://右移

                        if(info->cursor != info->tail){
                                info->cursor=info->cursor->next;
                                if(selectionMode)
                                    select++;//選取模式往右
                            }
                        break;

                    case 'I'://移到最頭
                        /*info->cursor=NULL;
                        break;*/

                    case 'A'://移到最尾
                        /*info->cursor=info->tail;
                        break;*/

                    case 'V'://SelectionMode

                        if(selectionMode){//原本已經selectionMode,現在要關掉
                            selectStart=NULL;
                        }
                        else{//原本不在selectionMode,現在要進入
                            selectStart=info->cursor;
                            select=0;//紀錄選取的方向
                        }
                        selectionMode=!selectionMode;
                        break;

                    case 'D'://Delete
                        if(selectionMode && select!=0){
                            info=Delete(selectStart , info , select);
                            selectionMode=!selectionMode;
                        }
                        break;
                    case 'R'://Reverse
                    default:
                    break;
                }
            }
            j++;
        }

        DoubleLL *temp=info->head->next;
        while(temp!=NULL){
            printf("%c",temp->letter);
            temp=temp->next;
        }
        printf("\n");
        info=genInfo();

    }
    


    return 0;
}