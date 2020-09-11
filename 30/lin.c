#include "akihabara.h"
#include <stdio.h>
#define HASHSIZE 73698513

int Array[50000000];
int headOfHashtable[HASHSIZE];
int tableOfChaining[50000001][2];  // [0] for next pointer, [1] for number of same value
long long int intervalSum[50000000];
        
int main(void) 
{
        unsigned int N = getN();
        long long int K = getK();
        getArray(N, Array);
                
        long long int diff, modulo, numMatchingInterval = 0;
        intervalSum[0] = Array[0];
        if (intervalSum[0] == K)
                ++numMatchingInterval;
        modulo = intervalSum[0] % HASHSIZE;
        if (modulo < 0) 
                modulo += HASHSIZE;
        headOfHashtable[modulo] = 1;
	tableOfChaining[1][1] = 1;
                
        for (int i = 1; i < N; i++) {
                intervalSum[i] = intervalSum[i - 1] + Array[i];
                diff = intervalSum[i] - K;
                modulo = diff % HASHSIZE;
                if (modulo < 0)
                        modulo += HASHSIZE;
                if (!diff) 
                        ++numMatchingInterval;
                for (int index = headOfHashtable[modulo]; index != 0; index = tableOfChaining[index][0]) {
                        if (intervalSum[index - 1] == diff) {
                                numMatchingInterval += tableOfChaining[index][1];                              
                                break;
                        }
                }
                
                modulo = intervalSum[i] % HASHSIZE;
                if (modulo < 0)
                        modulo += HASHSIZE;
                if (headOfHashtable[modulo] == 0) { 
                        headOfHashtable[modulo] = i + 1;
                        tableOfChaining[i + 1][1] = 1;
                } else { 
                        for (int index = headOfHashtable[modulo]; ; index = tableOfChaining[index][0]) {
                                if (intervalSum[index - 1] == intervalSum[i]) {                                
                                        ++tableOfChaining[index][1]; 
                                        break; 
                                } 
                                if (tableOfChaining[index][0] == 0) { 
                                        tableOfChaining[index][0] = i + 1;    
                                        tableOfChaining[i + 1][1] = 1; 
                                        break; 
                                } 
                        } 
                } 
        } 
 
        printf("%lld\n", numMatchingInterval);
        return 0;
}
