#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

typedef struct node{
    int count;
    int virus;
    struct node *next;
} Node;

Node *getPeople(){
    Node *N =(Node*)malloc(sizeof(Node));
    assert(N != NULL);
    N->next = NULL;
    N->count = 0;
    return N;
}

Node *getVirus(){
    Node *N =(Node*)malloc(sizeof(Node));
    assert(N != NULL);
    N->next = N;
    N->count = 0;
    return N;
}

Node *FindVirus(Node *p){
    Node *temp = p;
    if(temp == NULL)
        return NULL;
    
    while(temp->next != temp){
        temp = temp->next;
        if(temp == NULL)
            break;
    }
    return temp;
}

char s[3];
Node *people[1000002];
Node *virusIndex[1000002];

int main() {
    int N,M;
    scanf("%d%d",&N,&M);
    int p,q,v;
    // char s[10];
    int nextVirus=1;

    //Make_set
    // Node **people =(Node**)malloc(sizeof(Node*)*(N+1));
    // Node **virusIndex =(Node**)malloc(sizeof(Node*)*(M+1));
    for(int j=1;j<M+1;j++){
        virusIndex[j] = getVirus();
        virusIndex[j]->virus = j;
        // printf("%d\n",virusIndex[j]->virus);
    }

    for(int i=1;i<N+1;i++){
        people[i] = getPeople();
    }

    // for(int i=0;i<M;i++){
    //     scanf("%s",s);
    //     printf("%s\n",s);
    // }

    for(int i=0;i<M;i++){
        // printf("i = %d\n",i);
        // scanf("%c",&c);
        // printf("%c\n",c);
        
        scanf("%s",s);
        // printf("%s\n",s);

        switch(s[0]){
            case 'w'://感染
                scanf("%d",&p);
                // printf("%d\n",p);
                Node *root = FindVirus(people[p]);
                if(root){
                    root->count--;
                }
                people[p]->next = virusIndex[nextVirus];
                virusIndex[nextVirus]->count++;
                nextVirus++;
                break;

            case 'u'://傳染
                scanf("%d%d",&p,&q);
                // printf("%d %d\n",p,q);
                Node *root_p = FindVirus(people[p]), *root_q = FindVirus(people[q]);
                if(root_p && !root_q){//p感染q
                    root_p->count++;
                    people[q]->next = root_p;
                }else if(!root_p && root_q){//q感染p
                    root_q->count++;
                    people[p]->next = root_q;
                }else{//p,q都有感染
                    if(root_p->virus > root_q->virus){//p比較新
                        root_p->count+=root_q->count;
                        root_q->count = 0;
                        root_q->next = root_p;
                    }else if(root_p->virus < root_q->virus){//q比較新
                        root_q->count+=root_p->count;
                        root_p->count = 0;
                        root_p->next = root_q;
                    }
                }
                break;

            case 'h'://治癒
                scanf("%d",&p);
                // printf("%d\n",p);
                if(people[p]->next != NULL){
                    Node *root = FindVirus(people[p]);
                    root->count--;
                    people[p]->next = NULL;
                }
                break;
                
            case 'a'://印出感染virus種類
                scanf("%d",&p);
                printf("%d\n",1);
                // // printf("%d\n",p);
                // if(people[p]->next == NULL)
                //     printf("%d\n",0);
                // else{
                //     Node *root = FindVirus(people[p]);
                //     printf("%d\n",root->virus);
                // }
                break;

            case 'n'://印出感染該virus的人數
                scanf("%d",&v);
                // printf("%d\n",v);
                printf("%d\n",virusIndex[v]->count);
                break;
        }
    }
    return 0;
}