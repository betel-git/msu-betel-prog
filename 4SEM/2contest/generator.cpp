#include <cstdio>
#include <cstdlib>

double rnd()
{
    return double(rand())/RAND_MAX * 40 - 20;
}

int main()
{
    int n = 500;
    FILE *f = fopen("data.txt","w");
    for (int i=0; i<n; i++) {
        fprintf(f, "%4d %10.4f %10.4f %10.4f\n", i, rnd(), rnd(), rnd());
    }
    fclose(f);
    return 0;
}

