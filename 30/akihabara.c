#include"akihabara.h"
#include<stdio.h>
#include<stdlib.h>
char status=0;
unsigned int getN(){
  if(status!=0){
    fprintf(stderr,"call getN in wrong order!");
    exit(1);
  }
  status=1;
  unsigned int N;
  scanf("%u",&N);
  return N;
}
long long int getK(){
  if(status!=1){
    fprintf(stderr,"call getK in wrong order!");
    exit(1);
  }
  status=2;
  long long int K;
  scanf("%lld",&K);
  return K;
}
void getArray(unsigned int N,int array[]){
  if(status!=2){
    fprintf(stderr,"call getArray in wrong order!");
    exit(1);
  }
  status=3;
  for(unsigned int i=0;i<N;i++)
    scanf("%d",&array[i]);
  return;
}
