#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


/*
int main(void){

    char s[3000000], *ans=(char*)malloc(sizeof(char)*3000000);
    scanf("%s",s);
    int m;
    scanf("%d",&m);
    int l,r;
    scanf("%d%d",&l,&r);
    int d=r-l+1, cur=0,cmp;
    
    strncpy(&ans[cur],&s[l-1],d);
    cur += d;
    cmp = cur-1;

    for(int i=0;i<m-1;i++){
        scanf("%d%d",&l,&r);
        while(ans[cmp] == s[l-1] && (l<r || l==r ) && cmp>-1 ){
            l++;
            cmp--;
        }
            d = r-l+1;
            strncpy(&ans[cur],&s[l-1],d);
            cur += d;
            cmp = cur-1;

    }
    printf("%s\n",ans);

    return 0;
}*/


int main(void){

    char s[3000000], *ans=(char*)malloc(sizeof(char)*3000000);
    scanf("%s",s);
    int m;
    scanf("%d",&m);
    int l,r;
    scanf("%d%d",&l,&r);
    int d=r-l+1, cur=0,cmp;
    
    strncat(ans,&s[l-1],d);
    cur += d;
    cmp = cur-1;

    for(int i=0;i<m-1;i++){
        scanf("%d%d",&l,&r);
        while(ans[cmp] == s[l-1] && (l<r || l==r ) && cmp>-1 ){
            l++;
            cmp--;
        }
            d = r-l+1;
            strncat(ans,&s[l-1],d);
            cur += d;
            cmp = cur-1;

    }
    printf("%s\n",ans);

    return 0;
}
