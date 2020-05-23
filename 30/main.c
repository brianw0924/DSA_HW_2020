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
int main() {
    unsigned int N = getN();
    long long int K = getK();
    getArray(N, Array);

    int count = 0;
    int cur=0,*nextNegative=(int*)malloc(sizeof(int)*(N+1));
    long long int *hash =(long long int*)malloc(sizeof(long long int)*(N+1));
    hash[0] = 0;
    hash[1] = Array[0];
    int i;
    for(i=2;i<(N+1);i++){
        hash[i] = hash[i-1] + Array[i-1];
        if(Array[i-2]<0){
            for(int j=cur;j<(i-2);j++)
                nextNegative[j]=i-2;
            cur = i-1;
        }
        // printf("%llu ",hash[i-1]);
    }
    // printf("%llu\n",hash[N]);
    for(int j=cur;j<(N-1);j++)
        nextNegative[j]=N-1;
    nextNegative[N-1] = N;
    nextNegative[N] = N+1;
    // for(int k=0;k<N;k++)
    //     printf("nextNegative=%d\n",nextNegative[k]);
    // for(int k=0;k<N;k++)
    //     printf("%llu ",hash[k]);
    // printf("%llu\n",hash[N]);

    
    int l=0,r=1;
    while(l<N){
        // printf("l = %d\n",l);
        while(r<(N+1)){
            // printf("current l = %d, r = %d\n",l,r);
            // if(hash[r]-hash[l] == K)
            //     count++;
            // r++;
            if(hash[r]-hash[l] == K){
                // printf("l=%d r=%d\n",l,r);
                count++;
                r = nextNegative[r];
                // printf("next r = %d\n",r);
            }else if(hash[r]-hash[l] < K)
                r++;
            else
                r = nextNegative[r];
        }
        l++;
        r=l+1;
    }
    printf("%d\n",count);
}