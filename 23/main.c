#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

int main() {
    char *str = (char*)malloc(sizeof(char)*1000000);
    scanf("%s",str);
    //hash左邊位數小
    unsigned long long int *hash=(unsigned long long int*)malloc(sizeof(unsigned long long int)*1000000);
    hash[0] = str[0]-'a';
    unsigned long long int *table26=(unsigned long long int*)malloc(sizeof(unsigned long long int)*1000000);
    table26[0]=1;
    table26[1]=26; 
    unsigned long long int d = 26;

    int i=1;
    // printf("0 , %llu\n", hash[0]);
    while(str[i]!='\0'){
        hash[i] = hash[i-1] + d*(str[i]-'a');
        // printf("%d , %llu\n", i,hash[i]);
        i++;
        d*=26;
        table26[i] = d ;
        // printf("%d , table26 = %llu\n",i,table26[i]);
    }

    int m;
    scanf("%d",&m);
    
    int l,r;
    char *ans = (char*)malloc(sizeof(char)*3000000);

    scanf("%d%d",&l,&r);
    r--;
    l--;


    //ansHash 右邊位數小
    unsigned long long int *ansHash=(unsigned long long int*)malloc(sizeof(unsigned long long int)*1000000);
    //先處理第一個進來的substring
    ansHash[0] =str[l] - 'a';
    int len = r-l+1;
    int last=(len-1);
    strncpy(&ans[0],&str[l],len);
    // printf("ansHash = 0 , %llu\n",ansHash[i]);
    for(int i=1;i<len;i++){//建output的hash
        ansHash[i] = ansHash[i-1]*26 + (str[l+i]-'a');
        // printf("ansHash = %d , %llu\n", i ,ansHash[i]);
    }
    // printf("\n");
    

    for(int i=1;i<m;i++){
        scanf("%d%d",&l,&r);
        r--;
        l--;
        len = r-l+1;
        // printf("last=%d len=%d\n",last,len);

        //開始比較需要消除的部分
        if((last+1) < len){//新進來的substring比較長

            unsigned long long int cmpans = ansHash[last];
            int j=0,tempr=l+last;
            while( (tempr>(l-1) && ((hash[tempr]-hash[l-1]) != cmpans*table26[l]))){
                // printf("tempr = %d ",tempr);
                // printf("hash[%c] cmp=%llu vs ",ans[j],cmpans*table26[l]);
                // printf("hash[%c] %llu\n",str[tempr],(hash[tempr]-hash[l-1]));
                cmpans =ansHash[last] - ansHash[j]*table26[last-j];
                j++;
                tempr--;
            }
            // printf("tempr = %d ",tempr);
            // printf("ansHhash[%c] cmp=%llu vs ",ans[j],cmpans*table26[l]);
            // printf("hash[%c] %llu\n",str[tempr],(hash[tempr]-hash[l-1]));

            strncpy(&ans[last+1],&str[tempr+1],r-tempr);

            for(int k=0;k<(r-tempr);k++){
                ansHash[last+1] = ansHash[last]*26 + (str[tempr+k+1]-'a');
                last++;
                // printf("ansHash = %d , %llu\n", last ,ansHash[last]);
            }

            // printf("%s\n\n",ans);

        }else if ((last+1) > len){//目前output比較長

            int j=last-len,tempr=r;
            // printf("l=%d j=%d tempr=%d\n",l,j,tempr);
            // while(tempr>(l-1)){

            while( (tempr>(l-1)) && ((hash[tempr]-hash[l-1]) != ((ansHash[last] - ansHash[j]*table26[last-j])*table26[l]) )){
                // printf("%d\n",j);
                // printf("tempr = %d ",tempr);
                // printf("ansHash[%c] %llu vs ",ans[j+1],(ansHash[last] - ansHash[j]*table26[last-j])*table26[l]);
                // printf("hash[%c] %llu\n",str[tempr],(hash[tempr]-hash[l-1]));
                // printf("%llu\n",(hash[r]-hash[l-1])/table26[l]);
                j++;
                tempr--;
            }
            // printf("hash[%c] %llu vs ",ans[j],(ansHash[last] - ansHash[j]*table26[last-j])*table26[l]);
            // printf("hash[%c] %llu\n",str[tempr],(hash[tempr]-hash[l-1]));


            strncpy(&ans[last+1],&str[tempr+1],r-tempr);
            
            for(int k=0;k<(r-tempr);k++){
                ansHash[last+1] = ansHash[last]*26 + (str[tempr+k+1]-'a');
                last++;
                // printf("ansHash = %d , %llu\n", last ,ansHash[last]);
            }
            // printf("%s\n\n",ans);

            // printf("%llu\n",ansHash[16]-ansHash[7]*table26[8]);
            // printf("%llu\n",(hash[46]-hash[32])/table26[33]);

        }else{//一樣長

            unsigned long long int cmpans = ansHash[last];
            // printf("cmp=%llu\n",cmpans);
            int j=0,tempr=r;
            // printf("%llu\n",(hash[r]-hash[l-1])/table26[l]);
            // printf("l=%d\n",l);
            while( (tempr>(l-1) && ((hash[tempr]-hash[l-1]) != cmpans*table26[l]))){
                // printf("%d , ",j);
                // printf("tempr = %d ",tempr);
                // printf("hash[%c] cmp=%llu vs ",ans[j],cmpans*table26[l]);
                // printf("hash[%c] %llu\n",str[tempr],(hash[tempr]-hash[l-1]));
                cmpans =ansHash[last] - ansHash[j]*table26[last-j];
                j++;
                tempr--;
            }
            // printf("tempr = %d ",tempr);
            // printf("ansHash[%c] cmp=%llu vs ",ans[j],cmpans*table26[l]);
            // printf("hash[%c] %llu\n",str[tempr],(hash[tempr]-hash[l-1]));

            // printf("%d %d\n",last+1,r-tempr);
            strncpy(&ans[last+1],&str[tempr+1],r-tempr);
            for(int k=0;k<(r-tempr);k++){
                ansHash[last+1] = ansHash[last]*26 + (str[tempr+k+1]-'a');
                last++;
                // printf("ansHash = %d , %llu\n", last ,ansHash[last]);
            }
            // printf("%s\n\n",ans);
        }
    }
        printf("%s\n",ans);


    
    
    return 0;
}




