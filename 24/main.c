#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*typedef struct{
    int top;
    char *str;
} Stack;

Stack *genStack(){
    Stack *S =(Stack*)malloc(sizeof(Stack));
    S->top = -1;
    S->str = malloc(sizeof(char)*3000000);
    return S;
}*/



int main(void){
    char s[3000000], *str=(char*)malloc(sizeof(char)*3000000);
    scanf("%s",s);
    int m;
    scanf("%d",&m);
    int l,r;
    scanf("%d%d",&l,&r);
    int d=r-l+1, cur=0,cmp;
    
    strncpy(&str[cur],&s[l-1],d);
    cur += d;
    cmp = cur-1;
    // printf("%s\n",str);

    for(int i=0;i<m-1;i++){
        scanf("%d%d",&l,&r);
        // printf("repeat : \n");
        while(str[cmp] == s[l-1] && (l<r || l==r ) && cmp>-1 ){
            // printf("cmp=%d l=%d\n",cmp,l);
            // printf("%c\n",str[cmp]);
            l++;
            cmp--;
        }
            d = r-l+1;
            strncpy(&str[cur],&s[l-1],d);
            cur += d;
            cmp = cur-1;

    // printf("%s\n",str);

    }
    printf("%s\n",str);
    // char s[20],str[20];
    // scanf("%s",s);
    // int top=0 , l1 ,r1;
    // scanf("%d%d",&l1,&r1);
    // strncpy(&str[0] , s , r1-l1);
    // printf("%s",str);
    // scanf("%s%d%d",s,&l1,&r1);
    // strncpy(&str[5],s,r1-l1);
    // printf("%s",str);

    return 0;
}