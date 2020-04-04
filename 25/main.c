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

Info *Reverse(Info *info , Selection *start, Selection *end){

    if(start->next == end->cur){//只有反轉一個字 = 直接回傳
        return info;
    }



    //先把cursor,prev,next移動
    if(info->cursor == start->cur)//cursor停在start
        info->next = end->cur;
    else{//cursor停在end
        info->next = end->next;
        info->cursor = start->next;
        info->prev = XOR(start->cur , start->next->ptr); 
    }

    start->cur->ptr = XOR(start->prev , end->cur);
    end->cur->ptr = XOR(start->cur , end->prev);
    end->prev = XOR(start->cur , start->next->ptr);
    start->next->ptr = XOR( end->prev,end->next);

    if(end->cur == info->tail)
        info->tail = start->next;
    else
        end->next->ptr = XOR(start->next , XOR(end->cur , end->next->ptr));

    

    Node *temp = start->next;

    start->next = end->cur;
    end->cur = temp;



    return info;

}


void Print(Info *info){
        Node *temp,*cur,*prev;
        cur = info->head->ptr;
        prev = info->head;
        
        while(cur!=NULL){
            temp = cur;
            printf("%c",cur->letter);
            cur = XOR(prev , cur->ptr);
            prev = temp;
        }
        printf("\n");
}

//MAIN

int main(void){
    int T;
    scanf("%d",&T);

    Info *info=genInfo();

    char *str=(char*)malloc(sizeof(char)*1000000);

    int letter;
    bool selectionMode=false;
    Node *temp;
    Selection *S_temp;
    Selection *start=genSelection(),*end=genSelection();

    
    for(int i=0;i<T;i++){
        scanf("%s",str);

        int j=0;
        while(str[j]!='\0'){

            //printf("%c\n",str[j]);
            
            letter = (int)str[j];

            if (islower(letter)){//a~z

                Node *new=genNode(letter);//產生新的node

                if(selectionMode){

                    if(start->cur != end->cur)
                        info = Overwrite(info,new,start,end);
                    else //沒選取任何東西 直接寫完之後跳出selectionMode
                        info = Insert(info,new);
                    selectionMode=!selectionMode;

                }else

                    info = Insert(info,new);
                
            }else{//指令

                switch (str[j]){

                    case 'H'://左移

                        temp=info->cursor;

                        if(info->prev != NULL){//不在最左邊才移動
                            info->next = info->cursor;
                            info->cursor = info->prev;
                            info->prev = XOR(info->next , info->cursor->ptr);
                        
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
                        }
                        
                        break;
                    case 'L'://右移

                        temp = info->cursor;

                        if(info->next != NULL){//移動
                            info->prev = info->cursor;
                            info->cursor = info->next;
                            info->next = XOR(info->prev , info->cursor->ptr);
                        
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
                        }

                        break;
                    case 'I'://移到最頭
                        if(selectionMode){
                            if(info->cursor == start->cur){//直接移
                                info->prev = NULL;
                                info->cursor = info->head;
                                info->next = info->head->ptr;
                                start->cur = info->cursor;
                                start->prev = info->prev;
                                start->next = info->next;
                            }else{
                                S_temp = start;
                                
                                info->prev = NULL;
                                info->cursor = info->head;
                                info->next = info->head->ptr;
                                start->cur = info->cursor;
                                start->prev = info->prev;
                                start->next = info->next;

                                end->cur = S_temp->cur;
                                end->prev = S_temp->prev;
                                end->next = S_temp->next;
                            }
                        }else{
                            info->prev = NULL;
                            info->cursor = info->head;
                            info->next = info->head->ptr;
                        }
                        
                        break;

                    case 'A'://移到最尾
                        if(selectionMode){
                            if(info->cursor == end->cur){
                                info->next = NULL;
                                info->cursor = info->tail;
                                info->prev = info->tail->ptr;
                                end->cur = info->cursor;
                                end->prev = info->prev;
                                end->next = info->next;
                            }else{
                                S_temp = end;
                                
                                info->next = NULL;
                                info->cursor = info->tail;
                                info->prev = info->tail->ptr;
                                end->cur = info->cursor;
                                end->prev = info->prev;
                                end->next = info->next;

                                start->cur = S_temp->cur;
                                start->prev = S_temp->prev;
                                start->next = S_temp->next;
                                
                            }
                        }else{
                            info->next = NULL;
                            info->cursor = info->tail;
                            info->prev = info->tail->ptr;
                        }
                        break;

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
                        if(selectionMode && start->cur != end->cur){
                            info = Reverse(info,start,end);
                            //Print(info);
                        }
                        break;
                        
                        
                    default:
                    break;
                }
            }
            j++;
            
        }

        Print(info);
        info=genInfo();
        start=genSelection();
        end=genSelection();

    }
    


    return 0;
}