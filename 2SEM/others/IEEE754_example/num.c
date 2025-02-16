#include<stdio.h>

void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);
void test7(void);
void test8(float x);
void test9(void);


int main(void)
{
//    test1();
//   test2();
//   test3();
//   test4();
   test5();
//   test6();
//   test7();
//   test8(42);
//   test8(-10);
//   test9();
   return 0;
}


void test1(void)    // РѕРєСЂСѓРіР»РµРЅРёРµ РґР°РЅРЅС‹С…
{
    float a, b, c;
    a = 123456789;
    b = 123456788;   // СЂР°Р·РЅРѕСЃС‚СЊ = 1   
    c = a - b;  
    printf("test1: %f\n", c);
}


void test2(void)    // СЂР°Р·РЅС‹Рµ С‚РёРїС‹
{
    float a;
    double b, c, d, r;
    a = 123456789.123457;
    b = 123456789.123457;     
    d = 123456789.123457;
    c = a - b;  
    r = d - b;  
    printf("test2: %f  %f\n", c, r);
}

void test3(void)    // РѕРїСЏС‚СЊ СЂР°Р·РЅС‹Рµ С‚РёРїС‹
{
    float a, b, c;
    float c0, c1, c2;
    a = 1;
    b = 3;     
    c = a / b;        // С‚.Рµ. 1/3
    c0 = c - 1.0/3.0;    
    c1 = c - (float)1.0/(float)3.0;    
    c2 = c - 1.0f/3.0f;    
    printf("test3: %e %e %e\n", c0, c1, c2);
}


void test4(void)    // СЂР°Р·РЅС‹Рµ РјР°СЃС€С‚Р°Р±С‹
{
    double a, b;
    a = 1e+20;
    b = a + 1;
    if (b <= a)  printf("test4: something strange: a+1 <= a !!!\n");
}   


void test5(void)    // РЅР°РєРѕРїР»РµРЅРёРµ РїРѕРіСЂРµС€РЅРѕСЃС‚Рё
{
    int k, n = 1000000;
    float s1=0, s2=0;                                  
    for (k=1; k<n; k++) {
       s1 += 1.0f/k;
       s2 += 1.0f/(n-k);
    }
    printf("test5: s1 - s2 should be 0, but it is %e  %e\n", s1 - s2, s1);
}


void test6(void)    // СЃРµСЂРµРґРёРЅР° РѕС‚СЂРµР·РєР°
{
    float a=1, b=3, c;
    int k=0;
    while (1) {
       c = (a + b)/2;
       if (c <= a || c >=b) {
          printf("test6: This cannot be real !!!  %d\n",k);
          break; 
       }
       ++k;
       b = c;
    }
}


void test7(void)    // РґРІР° Р±Р»РёР¶Р°Р№С€РёС… РїСЂРµРґСЃС‚Р°РІРёРјС‹С…
{
    int i;
    //float a = 1, b = 0.5;
    double a = 1, b = 0.5;
    printf("test7:\n");
    for (i=0; a + b > a; i++) {
        printf("%3d  b=%e\n", i, b);
        b /= 2; 
    }
}

void printbit(unsigned char c, int i);
void printsomebits(unsigned char c, int ihigh, int ilow);

void printbit(unsigned char c, int i)
{
    int k = (c & (1<<i)) >> i;
    putchar('0' + k);
}
void printsomebits(unsigned char c, int ihigh, int ilow)
{
    int k;
    for (k=ihigh; k>=ilow; k--) printbit(c, k);
}



void test8(float x)  // РїРµС‡Р°С‚СЊ РґРІРѕРёС‡РЅРѕРіРѕ РїСЂРµРґСЃС‚Р°РІР»РµРЅРёСЏ
{
    int sign, order, mantissa;
    double dmantissa;
    unsigned char *p = (unsigned char *)&x;
    printf("decimal  %f\n",x);
    printf("hex      %02x %02x %02x %02x\n", p[3], p[2],p[1], p[0]);  // little endian
    printf("binary   ");   

    printbit(p[3], 7);
    putchar(' ');
    printsomebits(p[3], 6, 0);
    printbit(p[2], 7);
    putchar(' ');
    printsomebits(p[2], 6, 0);
    printsomebits(p[1], 7, 0);
    printsomebits(p[0], 7, 0);
    putchar('\n');

    sign = (p[3] & 0x80) ? -1 : 0;
    order = (p[3] & 0x7f) << 1 | (p[2] >> 7);
    order -= 127;
    mantissa =  (p[2] & 0x7f) << 16 | (p[1] << 8) | p[0];
    dmantissa = 1.0 + (double)mantissa * (1.0/(1<<23));
    printf("sign %c  order %d  mantissa %f\n", sign ? '-':'+', order, dmantissa);

}

void test9(void)
{
    int i, n = 100;
    float r1 = 0, r2;
    float x = 1.23456789;
    float d;
    for (i = 0; i < n; i++) {
        r1 += x;
    }
    r2 = n*x;
    d = r1 - r2;
    printf("test9:  diff = %e   %e %e\n", d, r1, r2);
}


