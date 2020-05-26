#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "akihabara.h"

int Array[50000000];
int main(){
    unsigned int N = getN();
    long long int K = getK();
    getArray(N, Array);

    int count = 0;
    int cur=0,*nextNegative=(int*)malloc(sizeof(int)*(N+1));
    long long int *hash =(long long int*)malloc(sizeof(long long int)*(N+1));
    hash[0] = 0;
    int i;

    for(i=1;i<(N+1);i++){
        hash[i] = hash[i-1] + Array[i-1];
        if(Array[i-1]<0){
            for(int j=cur;j<i;j++)
                nextNegative[j]=i-1;
            cur = i;
        }
    }
    for(int j=cur;j<(N+1);j++)
        nextNegative[j]=N+1;
    // nextNegative[N-1] = N;
    // nextNegative[N] = N+1;
    
    int l=0,r=1;
    while(l<N){
        while(r<(N+1)){
            if(hash[r]-hash[l] == K){//hit
                count++;
                r = nextNegative[r];
            }else if(hash[r]-hash[l] < K)//太小
                r++;
            else//太大
                r = nextNegative[r];
        }
        l++;
        r=l+1;
    }
    printf("%d\n",count);

    return 0;
}


    //     for(i=2;i<(N+1);i++)
    //         hash[i] = hash[i-1] + Array[i-1];
    // }

    
    // int l=0,r=1;
    // while(l<N){
    //     while(r<(N+1)){
    //         if(hash[r]-hash[l] == K)
    //             count++;
    //         r++;
    //     }
    //     l++;
    //     r=l+1;
    // }
    // printf("%d\n",count);

    