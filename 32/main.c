#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

typedef struct vertex{
    int station;
    int passed;
    char color;
    bool depart;
} Vertex;

typedef struct adjlistnode{
    int station;
    struct adjlistnode *next;
} Adjlistnode;

typedef struct graph{
    Vertex *V;
    Adjlistnode **Adjlist;
    int size;
} Graph;

Graph *makeGraph(int size){
    Graph *G = (Graph*) malloc(sizeof(Graph));
    G->size = size;
    G->V = (Vertex*) malloc(sizeof(Vertex)*(size+1));
    G->Adjlist = (Adjlistnode**) malloc(sizeof(Adjlistnode*)*(size+1));
    for(int i=1;i<(size+1);++i){
        G->V[i].station = i;
        G->V[i].passed = 0;
        G->V[i].color = 'W';
        G->V[i].depart = false;
        G->Adjlist[i] = NULL;
    }
    return G;
}

Adjlistnode listStorage[2000000];
Adjlistnode *nextNode = &listStorage[0];
Adjlistnode *getNode(int station){
    nextNode->station = station;
    nextNode->next = NULL;
    Adjlistnode *temp = nextNode;
    nextNode++;
    return temp;
}
void connect(Graph *G,int u, int v){
    Adjlistnode *new = getNode(v);
    // printf("Connecting (%d,%d):\n",u,v);
    if(G->Adjlist[u]){
    Adjlistnode *temp = G->Adjlist[u]->next;
    G->Adjlist[u]->next = new;
    new->next = temp;
    }else
        G->Adjlist[u] = new;
}
void DFS(Graph *G,int start){
    G->V[start].color = 'G';
    if(G->V[start].depart == true)//如果他是學生起點的話就passed+1
            G->V[start].passed++;
    Adjlistnode *adj = G->Adjlist[start];//第一個start的相鄰node
    while(adj!=NULL){
        if(G->V[adj->station].color == 'W'){
            DFS(G,adj->station);
            (G->V[start]).passed+=(G->V[adj->station]).passed;
        }
        adj = adj->next;
    }
}
int Partition(int *A, int p, int r){
    int x = A[p];
    int i = p-1;//left
    int j = r+1;//right
    while(i<j){
        do{
            j--;
        }while(A[j]>x);
        do{
            i++;
        }while(A[i]<x);
        if(i<j){
            int temp = A[j];
            A[j] = A[i];
            A[i] = temp;
        }
        else
            return j;
    }
    return j;
}
void Quicksort(int *A , int p , int r){
    if(p<r){
        int q =Partition(A, p, r);
        Quicksort(A,p,q);
        Quicksort(A,q+1,r);
    }
}

int Partition_node(Graph *G, int p, int r){
    int x = G->V[p].passed;
    int i = p-1;//left
    int j = r+1;//right
    // printf("test\n");
    while(i<j){
        
        do{
            j--;
        }while(G->V[j].passed>x);

        do{
            i++;
        }while(G->V[i].passed<x);

        if(i<j){
            // printf("(%d,%d)\n",i,j);
            int temp = G->V[j].passed;
            G->V[j].passed = G->V[i].passed;
            G->V[i].passed = temp;
        }
        else
            return j;
    }
    return j;
}

void Quicksort_node(Graph *G,int p, int r){
    // printf("Round (%d,%d)\n",p,r);
    // for(int i=1;i<(G->size+1);++i){
    //         printf("%d ",G->V[i].passed);
    // }
    // printf("\n");
    if(p<r){
        int q =Partition_node(G, p, r);
        Quicksort_node(G,p,q);
        Quicksort_node(G,q+1,r);
    }
}
/* strategy:
   1.從1開始DFS
   2.越多人經過的點,weight要越高
   3.difficulty最大的放終點
*/
int main(void){
    int n,m;
    scanf("%d%d",&n,&m);
    Graph *G = makeGraph(n);
    //departure
    int start;
    for(int i=0;i<m;++i){
        scanf("%d",&start);
        G->V[start].depart = true;
    }
    //difficulty
    int *d =(int*) malloc(sizeof(int)*(n-1));
    for(int i=0;i<n;++i){
        scanf("%d",&d[i]);
    }

    // for(int i=0;i<n;++i){
    //     printf("%d ",d[i]);
    // }
    // printf("\n");
    Quicksort(d,0,n-1);
    // for(int i=0;i<n;++i){
    //     printf("%d ",d[i]);
    // }
    // printf("\n");

    //edge
    int u,v;
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        connect(G,u,v);
        connect(G,v,u);
    }

    //DFS
    DFS(G,1);
    // for(int i=1;i<(n+1);++i){
    //     printf("%d ",G->V[i].passed);
    // }
    // printf("\n");
    Quicksort_node(G,1,n);


    int sum=0;
    for(int i=n-1;i>=1;--i){
        // printf("%d,%d\n",G->V[i].passed,d[i-1]);
        sum+=(d[i-1]*G->V[i].passed);
    }
    printf("%d\n",sum);


    return 0;
}