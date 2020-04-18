#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

int main() {
    char *str = (char*)malloc(sizeof(char)*1000002);
    scanf("%s",str);
    int n=strlen(str);

    unsigned long long *hash=(unsigned long long*)malloc(sizeof(unsigned long long)*1000002);
    unsigned long long *table26=(unsigned long long*)malloc(sizeof(unsigned long long)*3000002);

    unsigned long long d = 1;
    for(int i=0;i<n;i++){//26次方table
        table26[i] = d;
        // printf("%llu\n",table26[i]);
        d*=26;
    }

    int i=1;
    hash[0] = str[0]-'a';
    while(str[i]!='\0'){//題目字串的hash table, 左邊位數小
        hash[i] = hash[i-1] + table26[i]*(str[i]-'a');
        // printf("%llu\n",hash[i]);
        i++;
    }


    int m;
    scanf("%d",&m);
    
    int l,r;
    char *ans = (char*)malloc(sizeof(char)*3000002);

    scanf("%d%d",&l,&r);
    r--;
    l--;


    //ansHash 右邊位數小
    unsigned long long *ansHash=(unsigned long long*)malloc(sizeof(unsigned long long)*3000002);
    //先處理第一個進來的substring
    ansHash[0] =str[l] - 'a';
    int len = r-l+1;
    int last=(len-1);//目前ans[]最後一個字元的index
    strncpy(&ans[0],&str[l],len);
    for(int i=1;i<len;i++){//建output的hash
        ansHash[i] = ansHash[i-1]*26 + (str[l+i]-'a');
    }
    // printf("\n");
    

    for(int i=1;i<m;i++){
        scanf("%d%d",&l,&r);
        r--;
        l--;
        len = r-l+1;
        
        //開始比較需要消除的部分

        if((last+1) < len){//新進來的substring比較長

            unsigned long long cmpans = ansHash[last];//output字串的hash
            int j=0,tempr=l+last;

            if(l == 0){
                while( (tempr>(l-1) && (hash[tempr] != cmpans))){
                    cmpans =ansHash[last] - ansHash[j]*table26[last-j];
                    j++;
                    tempr--;
                }
            }else{
                while( (tempr>(l-1) && ((hash[tempr]-hash[l-1]) != cmpans*table26[l]))){
                    cmpans = ansHash[last] - ansHash[j]*table26[last-j];
                    j++;
                    tempr--;
                }
            }

            strncpy(&ans[last+1],&str[tempr+1],r-tempr);

            for(int k=0;k<(r-tempr);k++){//output的hash值更新
                ansHash[last+1] = ansHash[last]*26 + (str[tempr+k+1]-'a');
                last++;
            }


        }else if ((last+1) > len){//目前output比較長

            int j=last-len,tempr=r;
            unsigned long long cmpans = ansHash[last] - ansHash[j]*table26[last-j];//output字串的hash

            if(l == 0){
                while( (tempr>(l-1)) && (hash[tempr] != cmpans )){
                    j++;
                    cmpans = ansHash[last] - ansHash[j]*table26[last-j];
                    tempr--;
                }
            }else{
                while( (tempr>(l-1)) && ((hash[tempr]-hash[l-1]) != (cmpans*table26[l]) )){
                    j++;
                    cmpans = ansHash[last] - ansHash[j]*table26[last-j];
                    tempr--;
                }
            }


            strncpy(&ans[last+1],&str[tempr+1],r-tempr);
            
            for(int k=0;k<(r-tempr);k++){
                ansHash[last+1] = ansHash[last]*26 + (str[tempr+k+1]-'a');
                last++;
            }

        }else{//一樣長

            unsigned long long cmpans = ansHash[last];
            int j=0,tempr=r;
            if(l == 0){
                while( tempr>(l-1) && (hash[tempr] != cmpans)){
                    cmpans =ansHash[last] - ansHash[j]*table26[last-j];
                    j++;
                    tempr--;
                }
            }else{

                while( (tempr>(l-1) && ((hash[tempr]-hash[l-1]) != cmpans*table26[l]))){
                    cmpans =ansHash[last] - ansHash[j]*table26[last-j];
                    j++;
                    tempr--;
                }
            }

            strncpy(&ans[last+1],&str[tempr+1],r-tempr);
            for(int k=0;k<(r-tempr);k++){
                ansHash[last+1] = ansHash[last]*26 + (str[tempr+k+1]-'a');
                last++;
            }
            
            // printf("%s\n\n",ans);
            
        }
    }
        printf("%s\n",ans);


    
    
    return 0;
}




