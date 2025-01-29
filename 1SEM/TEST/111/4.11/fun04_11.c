#include "04_11.h"

int Bin(int x){
    int ans = 0, k = 1;
    while(x > 0){      
        ans += (x % 2) * k;
        k *= 10;
        x /= 2;
    }
    return ans;
}

int DecToDec4(int x){
    int y;
    int res = 0;
    for(int k = 0; x; k++){
        y = x % 10;
        res |= (y << (4 * k));
        x /= 10;
    }
    return res;
}


int Dec4ToDec(int y){
    int ans = 0;
    int x, k = 1;
    for(int i = 0; y; i++){
        x =(y & 0xf);
        ans += (x * k);
        k *= 10;
        y >>= 4;
    }
    return ans;
}


int Sum(int x, int y){
    int a, b, c = 0, d = 0;
    int ans = 0;
    x = DecToDec4(x);
    y = DecToDec4(y);
    for(int i = 0; i < 8; i++){
        a = x & (0xf << i * 4);
        a >>= i * 4;
        b = y & (0xf << i * 4);
        b >>= i * 4;
        d = a + b + c;
        if(d > 9){
            c = 1;
            d -= 10;
        }
        else c = 0;
        ans |= (d << (4 * i));
    }
    return ans;
}

