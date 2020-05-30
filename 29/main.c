#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#pragma GCC optimize("O3,Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

typedef struct node{
    int count;
    int virus;
    struct node *next;
} Node;


Node storage[2000005];
Node *nextNode = &storage[0];

Node *getPeople(){
    Node *N = nextNode;
    nextNode++;
    N->next = NULL;
    N->count = 0;
    return N;
}

Node *getVirus(){
    Node *N = nextNode;
    nextNode++;
    N->next = N;
    N->count = 0;
    return N;
}

Node *FindVirus(Node *p){
    Node *temp = p;
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
    int nextVirus=1;

    for(int j=1;j<1000003;j++){
        virusIndex[j] = getVirus();
        virusIndex[j]->virus = j;
    }

    for(int i=1;i<N+1;i++){
        people[i] = getPeople();
    }


    for(int i=0;i<M;i++){
        
        scanf("%s",s);

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

            case 'u'://傳染(BUG)
                scanf("%d%d",&p,&q);
                // printf("%d %d\n",p,q);
                Node *root_p = FindVirus(people[p]), *root_q = FindVirus(people[q]);
                if(root_p && !root_q){//p感染q
                    root_p->count++;
                    people[q]->next = root_p;
                }else if(!root_p && root_q){//q感染p
                    root_q->count++;
                    people[p]->next = root_q;
                }else if(root_p && root_q){//p,q都有感染
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
                // printf("%d\n",p);
                if(people[p]->next == NULL)
                    printf("%d\n",0);
                else{
                    Node *root = FindVirus(people[p]);
                    printf("%d\n",root->virus);
                }
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