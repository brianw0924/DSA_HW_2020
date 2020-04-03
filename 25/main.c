#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>


typedef struct node{
    char letter;
    struct node *ptr;
} Node;

Node *XOR(Node *a,Node *b){
    return (Node*)((unsigned long)(a) ^ (unsigned long)(b));
}

Node *genNode(char letter){
    Node *N=(Node*)malloc(sizeof(Node));
    N->letter=letter;
    N->ptr=NULL;
    return N;    
}

typedef struct{
    Node *head;
    Node *tail;
    Node *cursor;
    Node *prev;
    Node *next;
} Info;

typedef struct{
    Node *cur;
    Node *prev;
    Node *next;
} Selection;

Selection *genSelection(){
    Selection *S=(Selection*)malloc(sizeof(Selection));
    S->cur=NULL;
    S->prev=NULL;
    S->next=NULL;
    return S;
}

Info *genInfo(){
    Info *I=(Info*)malloc(sizeof(Info));
    Node *Begin=genNode('S');
    I->head=Begin;
    I->tail=Begin;
    I->cursor=Begin;
    I->prev=NULL;
    I->next=NULL;
    return I;
}

Info *Insert(Info *info , Node *new){
    if(info->cursor == info->tail){//cursor在尾端
        new->ptr = XOR(info->cursor , NULL);
        info->cursor->ptr =  XOR((info->cursor->ptr) , new);

        info->prev = info->cursor;
        info->tail = new;
        info->cursor = new;
    }
    else{//cursor在中間
        
        new->ptr = XOR(info->cursor,info->next);
        info->next->ptr = XOR(new , XOR(info->cursor , info->next->ptr));
        info->cursor->ptr = XOR(info->prev , new);

        info->prev = info->cursor;
        info->cursor = new;
    }

    return info;
}

Info *Overwrite(Info *info , Node *new , Selection *start , Selection *end){

    new->ptr = XOR(start->cur , end->next);
    start->cur->ptr = XOR(start->prev , new);

    if(end->cur == info->tail)
        info->tail = new;
    else
        end->next->ptr = XOR(new , XOR(end->cur , end->next->ptr));

    info->cursor = new;
    info->prev = start->cur;
    info->next = end->next;

    return info;
}

Info *Delete(Info *info , Selection *start, Selection *end){
    start->cur->ptr = XOR(start->prev , end->next);
    if(end->cur == info->tail)
        info->tail = start->cur;
    else
        end->next->ptr = XOR(start->cur , XOR(end->cur , end->next->ptr));

    info->prev = start->prev;
    info->cursor = start->cur;
    info->next = end->next;

    return info;

}





int main(void){
    int T;
    scanf("%d",&T);

    Info *info=genInfo();

    char *str=(char*)malloc(sizeof(char)*1000000);

    int letter;
    bool selectionMode=false;
    Node *temp;
    Selection *start=genSelection(),*end=genSelection();

    
    for(int i=0;i<T;i++){
        scanf("%s",str);

        int j=0;
        while(str[j]!='\0'){

            //printf("%c\n",str[j]);
            
            letter = (int)str[j];

            if (islower(letter)){//a~z
                Node *new=genNode(letter);

                if(selectionMode){
                    if(start->cur != end->cur)
                        info = Overwrite(info,new,start,end);
                    else 
                        info = Insert(info,new);
                    selectionMode=!selectionMode;
                }else
                    info = Insert(info,new);
                
            }else{//指令

                switch (str[j]){

                    case 'H'://左移
                        temp=info->cursor;
                        if(info->prev != NULL){//移動
                            info->next = info->cursor;
                            info->cursor = info->prev;
                            info->prev = XOR(info->next , info->cursor->ptr);
                        }
                        if(selectionMode){
                            if(temp == start->cur){
                                start->cur = info->cursor;
                                start->prev = info->prev;
                                start->next = info->next;
                            }
                            else{
                                end->cur = info->cursor;
                                end->prev = info->prev;
                                end->next = info->next;
                            }
                        }
                        
                        break;
                    case 'L'://右移
                        temp = info->cursor;

                        if(info->next != NULL){//移動
                            info->prev = info->cursor;
                            info->cursor = info->next;
                            info->next = XOR(info->prev , info->cursor->ptr);
                        }


                        if(selectionMode){
                            if(temp == end->cur){
                                end->cur = info->cursor;
                                end->prev = info->prev;
                                end->next = info->next;
                            }
                            else{
                                start->cur = info->cursor;
                                start->prev = info->prev;
                                start->next = info->next;
                            }
                        }

                        break;
                    case 'I'://移到最頭
                        /*info->cursor=NULL;
                        break;*/

                    case 'A'://移到最尾
                        /*info->cursor=info->tail;
                        break;*/

                    case 'V'://SelectionMode
                        if(!selectionMode){
                            start->cur = info->cursor;
                            start->prev = info->prev;
                            start->next = info->next;
                            end->cur = info->cursor;
                            end->prev = info->prev;
                            end->next = info->next;
                        }
                        selectionMode = !selectionMode;
                        break;
                    case 'D'://Delete
                        if(selectionMode && start->cur != end->cur){
                            info = Delete(info,start,end);
                            selectionMode = !selectionMode;
                        }
                        break;
                    case 'R'://Reverse
                        
                    default:
                    break;
                }
            }
            j++;
        }

        info->cursor = info->head->ptr;
        info->prev = info->head;

        while(info->cursor!=NULL){
            temp = info->cursor;
            printf("%c",info->cursor->letter);
            info->cursor = XOR(info->prev , info->cursor->ptr);
            info->prev = temp;
        }
        printf("\n");
        info=genInfo();
        start=genSelection();
        end=genSelection();

    }
    


    return 0;
}