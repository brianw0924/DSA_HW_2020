#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
    char str[1000002],ans[3000002];
    unsigned long long hash[1000002], ansHash[3000002], table26[1000002];


int main() {
    scanf("%s",str);
    int n = strlen(str);

    hash[n-1] = str[n-1] - 'a';
    for(int i=n-2;i>=0;i--)
        hash[i] = hash[i+1]*26 + (str[i] - 'a');

    table26[0]=1;
    for(int i=1;i<n;i++)
        table26[i]=table26[i-1]*26;
    
    int m;//讀幾次
    scanf("%d",&m);
    int r,l,last;
    scanf("%d%d",&l,&r);
    l--;//讓index從0開始
    r--;
    int len = r-l+1;
    last = len-1;
    //先處理第一個進來的字串
    strncpy(ans,&str[l],len);
    ansHash[0]=ans[0]-'a';
    for(int i=1;i<len;i++)
        ansHash[i] = ansHash[i-1]*26 + (ans[i] - 'a');
    

    n--;//n現在是str[]的最後一個字元之index
    for(int i=1;i<m;i++){
        scanf("%d%d",&l,&r);
        l--;
        r--;
        int len = r-l+1;
        if(len < (last+1)){//新進來的substring比較短
            int j = last - len; //j指在要被刪除的地方
            int tempr = r;

            unsigned long long cmpans = ansHash[last] - ansHash[j]*table26[last-j];
            unsigned long long cmpnew = hash[l] - hash[tempr+1]*table26[tempr-l+1];

                for(int k=0;k<len && cmpans != cmpnew ;k++){
                    j++;
                    tempr--;
                    cmpans = ansHash[last] - ansHash[j]*table26[last-j];
                    cmpnew = hash[l] - hash[tempr+1]*table26[tempr-l+1];
                }
                int cpylen = r -tempr;
                strncpy(&ans[last+1] , &str[tempr+1] , cpylen);
                //更新ansHash
                for(int k=0;k<cpylen;k++){
                    ansHash[last+1] = ansHash[last]*26 + (str[tempr+1+k] -'a');
                    last++;
                }
            
        }else{//新進來的substring比較長 or 一樣長
            int tempr = l+last;
            int j = -1;
            unsigned long long cmpans = ansHash[last] - ansHash[j]*table26[last-j];
            unsigned long long cmpnew = hash[l] - hash[tempr+1]*table26[tempr-l+1];

            for(int k=0;k<(last+1) && cmpans != cmpnew;k++){
                j++;
                tempr--;
                cmpans = ansHash[last] - ansHash[j]*table26[last-j];
                cmpnew = hash[l] - hash[tempr+1]*table26[tempr-l+1];
            }
            int cpylen = r -tempr;
            strncpy(&ans[last+1] , &str[tempr+1] , cpylen);
            //更新ansHash
            for(int k=0;k<cpylen;k++){
                ansHash[last+1] = ansHash[last]*26 + (str[tempr+1+k] -'a');
                last++;
            }

        }
    }


    
        printf("%s\n",ans);


    
    
    return 0;
}




