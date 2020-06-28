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

typedef struct vertex{
    int height;
} Vertex;

typedef struct listnode{
    int num;
    struct listnode *next;
} Listnode;

Listnode storage[1000002];//12000KB
Listnode *nextListnode = &storage[0];

typedef struct graph{
    long long int *d;
    Vertex *tower;
    Listnode **Adjlist;
    int V;
} Graph;

typedef struct heap{
    int size;
    int *arr;
} Heap;

Graph *makeGraph(int V, int E){
    Graph *G = (Graph*) malloc(sizeof(Graph));
    G->V = V;
    G->d = (long long int*) malloc(sizeof(long long int)*(V+1));//2000KB
    return G;
    for(int i=1;i<(V+1);++i)//這裡會RE!!!!!!!!!!!!!!!!!!!!
        G->d[i] = 1000000001;
    // return G;
    G->tower = (Vertex*) malloc(sizeof(Vertex)*(V+1));//2000KB
    // return G;
    G->Adjlist = (Listnode**) malloc(sizeof(Listnode*)*(V+1));//12000KB
    for(int i=1;i<(V+1);++i){
        G->Adjlist[i]= NULL;
    }
    return G;
}

void connect(Graph *G,int u, int v){
    Listnode *new = nextListnode;
    new->next = NULL;
    new->num = v;
    ++nextListnode;
    if(G->Adjlist[u]){
        Listnode *temp = G->Adjlist[u]->next;
        G->Adjlist[u]->next = new;
        new->next = temp;
    }else
        G->Adjlist[u] = new;
}

int parent(int i){
    return i/2;
}
int left(int i){
    return 2*i;
}
int right(int i){
    return 2*i+1;
}
int cmp(Graph *G, int i, int j){
    if(G->d[i] < G->d[j])
        return i;
    return j;
}

void heapify(Graph *G, Heap *h, int i){
    int min = i;
    int r = right(i);
    int l = left(i);
    if(r<(h->size+1)){
        min = cmp(G,r,cmp(G,i,l));
    }else if(l<(h->size+1)){
        min = cmp(G,l,i);
    }
    
    if(min != i){
        int temp = h->arr[i];
        h->arr[i] = h->arr[min];
        h->arr[min] = temp;
        heapify(G,h,min);
    }
    return;
}

Heap *makeHeap(Graph *G, int s){
    Heap *h = (Heap*) malloc(sizeof(Heap));
    h->size = G->V;
    h->arr = (int*) malloc(sizeof(int)*(h->size+1));//2000KB
    for(int i=1;i<(h->size+1);++i)
        h->arr[i] = i;
    int temp = h->arr[1];
    h->arr[1] = s;
    h->arr[s] = h->arr[1];
    // for (int i=1;i<(h->size+1);++i)
    //     printf("%d\n",h->arr[i]);
    return h;
}

int Extract_min(Graph *G,Heap *h){
    int temp = h->arr[1];
    h->arr[1] = h->arr[h->size--];
    heapify(G,h,1);
    return temp;
}


void Relax(Graph *G, int u, int v){
    if((G->tower[v].height) > (G->tower[u].height))
        G->d[v] = G->tower[v].height;
    else
        G->d[v] = G->d[u];
    // printf("vertex[%d] = %d\n",v,G->d[v]);
    return;
}

void Dijkstra(Graph *G,int s){
    G->d[s] = 0;
    Heap* h = makeHeap(G,s);
    // //debug
    // for (int i=1;i<(h->size+1);++i)
    //     printf("%d ",h->arr[i]);
    // printf("\n");
    // //debug
    while(h->size>0){
        int u = Extract_min(G,h);
        // //debug
        // for (int i=1;i<(h->size+1);++i)
        //     printf("%d ",h->arr[i]);
        // printf("\n");
        // //debug
        Listnode *temp = G->Adjlist[u];
        while(temp != NULL){
            Relax(G,u,temp->num);
            temp = temp->next;
        }
    }
}

int main(void){
    int N,M,s,t,u,v,height;
    scanf("%d%d",&N,&M);
    Graph *G = makeGraph(N,M);//這裡會RE!!!!!!!!!!!!!!!!!!!!!!
    return 0;
    //edge
    for(int i=0;i<M;++i){
        scanf("%d%d",&u,&v);
        connect(G,u,v);
        connect(G,v,u);
    }
    // for(int i=1;i<(N+1);++i){
    //     Listnode *temp = G->Adjlist[i];
    //     while(temp!=NULL){
    //         printf("%d",temp->num);
    //         temp = temp->next;
    //     }
    //     printf("\n");
    // }
    // printf("test\n");

    //height
    for(int i=1;i<(N+1);++i){
        scanf("%d",&G->tower[i].height);
        // printf("%d\n",G->tower[i].height);
    }

    scanf("%d%d",&s,&t);
    Dijkstra(G,s);
    printf("%llu\n",G->d[t]);

    
    return 0;
}