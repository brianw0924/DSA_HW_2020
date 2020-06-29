#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#pragma GCC optimize("no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

typedef struct listnode{
    int num;
    struct listnode *next;
} Listnode;

Listnode storage[1000002];
Listnode *nextListnode = &storage[0];

typedef struct graph{
    int d[500001],height[5000001];//花的最短時間 and 各塔高度
    Listnode **Adjlist;//相鄰串列
    int V;//塔數量
} Graph;

typedef struct heap{
    int size;
    int *arr;//裡面裝 "塔的編號"
    int *index;//裡面裝 "塔在heap的哪一格"
} Heap;

Graph *makeGraph(int V, int E){
    Graph *G = (Graph*) malloc(sizeof(Graph));
    G->V = V;
    // memset(&G->d[1],1000000001,sizeof(int)*V);
    for(int k=1;k<(V+1);++k){
        G->d[k] = 1000000001;
    }
    G->Adjlist = (Listnode**) malloc(sizeof(Listnode*)*(V+1));
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

void heapify(Graph *G, Heap *h, int i){
    int key = h->arr[i];
    int Indexkey = h->index[key];
    int j = i<<1;
    int size_plusone = h->size+1;

    while(j < size_plusone){//有左子
        if(j<h->size){//有右子
            if(G->d[h->arr[j]] > G->d[h->arr[j+1]])
                ++j;
        }//現在j為左子右子中最小的
        if(G->d[key] > G->d[h->arr[j]]){
            h->index[key] = h->index[h->arr[j]];
            h->index[h->arr[j]] = Indexkey;
            Indexkey = h->index[key];
            h->arr[j>>1] = h->arr[j];
            j = j<<1;
        }else
            break;
        h->arr[j>>1] = key;
    }
    return;
}

Heap *makeHeap(Graph *G, int s){
    Heap *h = (Heap*) malloc(sizeof(Heap));
    h->size = G->V;
    h->arr = (int*) malloc(sizeof(int)*(h->size+1));
    h->index = (int*) malloc(sizeof(int)*(h->size+1));
    for(int i=1;i<(h->size+1);++i){
        h->arr[i] = i;
        h->index[i] = i;
    }
    int temp = h->arr[1];
    h->arr[1] = s;
    h->arr[s] = temp;
    h->index[1] = s;
    h->index[s] = 1;

    return h;
}

int Extract_min(Graph *G,Heap *h){
    int temp = h->arr[1];
    h->index[h->arr[h->size]] = 1;
    h->index[h->arr[1]] = h->size;
    h->arr[1] = h->arr[h->size--];
    heapify(G,h,1);
    return temp;
}


void Relax(Graph *G, int u, int v){

    int vh = G->height[v], ud = G->d[u];
    if(vh > (G->height[u])){//v比u高
        if(ud < vh){
            if(G->d[v] > ud)
                G->d[v] = vh;
        }else{
            G->d[v] = ud;
        }


        // if(G->d[v] > G->d[u]){//v的最短天數 > u的最短天數
        //     if(G->d[u] < G->height[v]){//u的最短天數 < v的高度
        //         // if(G->d[v] > G->height[v])//v的最短天數 > v的height
        //         G->d[v] = G->height[v];
        //     }
        //     else//u的最短天數 >= v的高度
        //         G->d[v] = G->d[u];
        // }
    }
    else{//u比v高
        if(G->d[v]>G->d[u])//v的最短天數 > u的最短天數
            G->d[v] = G->d[u];
        
    }    
    // if((G->height[v]) > (G->height[u])){//v比u高
    //     if(G->d[u] < G->height[v]){
    //         if(G->d[v] > G->d[u])
    //             G->d[v] = G->height[v];
    //     }else{
    //         G->d[v] = G->d[u];
    //     }


    //     // if(G->d[v] > G->d[u]){//v的最短天數 > u的最短天數
    //     //     if(G->d[u] < G->height[v]){//u的最短天數 < v的高度
    //     //         // if(G->d[v] > G->height[v])//v的最短天數 > v的height
    //     //         G->d[v] = G->height[v];
    //     //     }
    //     //     else//u的最短天數 >= v的高度
    //     //         G->d[v] = G->d[u];
    //     // }
    // }
    // else{//u比v高
    //     if(G->d[v]>G->d[u]){//v的最短天數 > u的最短天數
    //         G->d[v] = G->d[u];
    //     }
    // }
    return;
}

void decrease_key(Graph *G, Heap *h, int v){
    int now = h->index[v];
    if(now<h->size+1){//防止被extract的點再被decrease
        int p;
        while(now>1){//調整heap
            p = now>>1;
            if(G->d[h->arr[p]] > G->d[h->arr[now]]){
                int temp = h->arr[p];
                h->arr[p] = h->arr[now];
                h->arr[now] = temp;
    
                temp = h->index[h->arr[p]];
                h->index[h->arr[p]] = h->index[h->arr[now]];
                h->index[h->arr[now]] = temp;
            }
            now = p;
        }
    }
}

void Dijkstra(Graph *G,int s){
    G->d[s] = 0;
    Heap* h = makeHeap(G,s);
    while(h->size>0){
        int u = Extract_min(G,h);
        Listnode *temp = G->Adjlist[u];
        while(temp != NULL){
            Relax(G,u,temp->num);
            decrease_key(G,h,temp->num);
            temp = temp->next;
        }
    }
}

int main(void){
    int N,M,s,t,u,v,height;
    scanf("%d%d",&N,&M);
    Graph *G = makeGraph(N,M);
    //edge
    int i;
    for(i=0;i<M;++i){
        scanf("%d%d",&u,&v);
        connect(G,u,v);
        connect(G,v,u);
    }
    //height
    for(i=1;i<(N+1);++i){
        scanf("%d",&G->height[i]);
    }
    scanf("%d%d",&s,&t);
    Dijkstra(G,s);
    printf("%d\n",G->d[t]);
    return 0;
}