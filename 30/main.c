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
    long long int *hash =(long long int*)malloc(sizeof(long long int)*(N+1));
    hash[0] = 0;
    hash[1] = Array[0];
    for(int i=2;i<(N+1);i++){
        hash[i] = hash[i-1] + Array[i-1];
        // printf("%llu ",hash[i-1]);
    }
    // printf("%llu\n",hash[N]);
    int l=0,r=1;
    while(l<N){
        while(r<(N+1)){
            if(hash[r]-hash[l] == K){
                count++;
            }
            r++;
        }
        l++;
        r=l+1;
    }
    printf("%d\n",count);
}