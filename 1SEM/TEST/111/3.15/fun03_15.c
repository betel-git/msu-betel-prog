#include "03_15.h"

void Radix_4_Bit(unsigned int *a, int n, unsigned int *b){
    int alf[16] = {0};
    int cnt, k;
    for(int j = 0; j < 8; j++){
        for(int i = 0; i < n; i++){
            alf[Test_4_Bit(a[i], j)]++;
        }
        cnt = 0;
        for(int i = 0; i < 16; i++){
            k = 0;
            while(alf[i]){
                if(k >= n) break;
                if(Test_4_Bit(a[k], j) == i){
                    alf[i]--;
                    b[cnt] = a[k];
                    cnt++;
                }
                k++;
            }
        }
        for(int i = 0; i < n; i++){
            a[i] = b[i];
        }
    }
}


int Test_4_Bit(unsigned int x, int k){
    int ans = 0;
    int bin = 1;
    for(int i = 0; i < 4; i++){
        //printf("%d ", (x >> (k * 4 + i)) & 1);
        ans += ((x >> (k * 4 + i)) & 1) * bin;
        bin *= 2;
    }
    //printf("\n%u  <%d>\n", x, ans);
    return ans;
}


int Cnt(unsigned int *a, int n){
    int cnt = 0;
    for(int i = 1; i < n; i++){
        if(a[i - 1] > a[i]) cnt++;
    }
    return cnt;
}


void Prn(unsigned int *a, int n){
    if(n > 20) n = 20;
    for(int i = 1; i < n; i++){
        printf("%d\n", a[i]);
    }
}


void Rand(int n){
    FILE *f;
    f = fopen("a", "w");
    for(int i = 0; i < n; i++){
        fprintf(f, "%d\n", rand() % 10000);
    }
    fclose(f);
}

int Init(unsigned int *a, int n, FILE *f){
    for(int i = 0; i < n; i++){
        if((fscanf(f, "%u", a + i)) != 1){
            return 0;
        }
    }
    return 1;
}
