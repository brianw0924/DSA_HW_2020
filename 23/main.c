#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

int main() {
    char *str = (char*)malloc(sizeof(char)*1000001);
    scanf("%s",str);
    unsigned long long int *hash=(unsigned long long int*)malloc(sizeof(unsigned long long int)*strlen(str));
    unsigned long long int *table26=(unsigned long long int*)malloc(sizeof(unsigned long long int)*3000000);

    unsigned long long int d = 1;
    for(int i=0;i<3000000;i++){//26次方table
        table26[i] = d;
        d*=26;
    }

    int i=1;
    hash[0] = str[0]-'a';
    while(str[i]!='\0'){//題目字串的hash table, 左邊位數小
        hash[i] = hash[i-1] + table26[i]*(str[i]-'a');
        i++;
    }


    int m;
    scanf("%d",&m);
    
    int l,r;
    char *ans = (char*)malloc(sizeof(char)*3000001);

    scanf("%d%d",&l,&r);
    r--;
    l--;


    //ansHash 右邊位數小
    unsigned long long int *ansHash=(unsigned long long int*)malloc(sizeof(unsigned long long int)*3000000);
    //先處理第一個進來的substring
    ansHash[0] =str[l] - 'a';
    int len = r-l+1;
    int last=(len-1);
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

            unsigned long long int cmpans = ansHash[last];
            int j=0,tempr=l+last;

            if(l == 0){
                while( (tempr>(l-1) && (hash[tempr] != cmpans))){
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


        }else if ((last+1) > len){//目前output比較長

            int j=last-len,tempr=r;
            if(l == 0){
                while( (tempr>(l-1)) && (hash[tempr] != (ansHash[last] - ansHash[j]*table26[last-j]) )){
                    j++;
                    tempr--;
                }
            }else{
                while( (tempr>(l-1)) && ((hash[tempr]-hash[l-1]) != ((ansHash[last] - ansHash[j]*table26[last-j])*table26[l]) )){
                    j++;
                    tempr--;
            }
            }


            strncpy(&ans[last+1],&str[tempr+1],r-tempr);
            
            for(int k=0;k<(r-tempr);k++){
                ansHash[last+1] = ansHash[last]*26 + (str[tempr+k+1]-'a');
                last++;
            }

        }else{//一樣長

            unsigned long long int cmpans = ansHash[last];
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




