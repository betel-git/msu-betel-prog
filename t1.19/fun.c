#include "fun.h"
void Function(FILE *inputFile){
    int bool = 1;
    int g, l;
	double temp;
    double a;
    for (int i = 0; fscanf(inputFile, "%lf\n", &a) == 1; i++) {
            if (i == 0) {
                g = 1;
                temp = a;
            }
            if (a <= temp && bool) { // неубывает, до этого возрастала
                g++;
                bool = 0;
            }
            else if ( a > temp && !bool) { // возрастает, до этого не возрастала
                l++;
                bool = 1;
            }
            temp = a;
    }
	if (g > l) {printf("Возрастающих больше\n");}
	else if (g < l) {printf("Невозрастающих больше\n");}
	else {printf("Равное количество\n");}
}