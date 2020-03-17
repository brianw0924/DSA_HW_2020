#include <stdio.h>
#include<stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


int main(void){
    char player[2][11];
    int playerIndex=0;
    scanf("%s%s",player[0],player[1]);

    char *N=(char*)malloc(sizeof(char)*30000001),*M=(char*)malloc(sizeof(char)*30000001);
    scanf("%s%s",N,M);
    char *tempM=(char*)malloc(sizeof(char)*strlen(M)+1);
    N=(char*)realloc(N,sizeof(char)*strlen(N)+1);
    M=(char*)realloc(M,sizeof(char)*strlen(M)+1);

    int coverage=0,pushSize=0;

    tempM[pushSize]=M[pushSize];
    tempM[pushSize+1]='\0';
    char *ptr=strstr(N,tempM);
    coverage++;


    bool win=0;

    while(!win){
        //printf("我要找的是 : %s\n",tempM->array);
        //printf("ptr=%s\n\n",ptr);
        if(strlen(tempM)==strlen(M)){//先檢查有沒有找到,如果現在要找的string 長度=Ｍ 代表找到了
            coverage%=1000000007;
            printf("%s\n%d\n",player[playerIndex],coverage);
            win=!win;
        }else{

        if(&ptr[strlen(tempM)]==NULL)//以防下一段開頭是NULL
            ptr=NULL;
        else
            ptr=strstr(&ptr[strlen(tempM)],tempM);
        
        if(ptr==NULL){//找不到下一個tempM了
            
            pushSize++;//等等要多推一個M進tempM
            tempM[pushSize]=M[pushSize];
            tempM[pushSize+1]='\0';
            ptr=strstr(N,tempM);//從頭開始找新的tempM
            coverage+=strlen(tempM);
            playerIndex++;
            playerIndex&=1;
            
        }
        else{
            coverage+=strlen(tempM);
            playerIndex++;
            playerIndex&=1;
        }
        }
    }

    free(N);
    free(M);
    free(tempM);
    
    return 0;
}
