#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int *PrefixFunction(char *str, int N){
    int *arr = (int*)malloc(sizeof(int) * N);
    arr[0]=0;
    int k=0;

    for(int q=1;q<N;q++){
        while(k>0 && str[k] != str[q])
            k = arr[k-1];
        if(str[k] == str[q])
            k++;
        arr[q] = k;
    }
    return arr;
}

int main(void){
    int N;
    scanf("%d",&N);
    char *str = (char*)malloc(sizeof(char) * N);
    scanf("%s",str);
    int *kmp = PrefixFunction(str,N);


    int *ans =(int*)malloc(sizeof(int) * N);
    for(int i=0;i<N;i++)
        ans[i]=i+1;

    
    for(int i=0;i<N;i++){
        int len = i+1;
        int j=len;
        while(kmp[i+j] == j && (i+j) < N){
            ans[i+j] = len;
            j+=len;
        }
        printf("%d: %d\n",i+1,ans[i]);
    }
    return 0;
}