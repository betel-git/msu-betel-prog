#include "greatestsequence.h"

double GreatestSequence(FILE *f) {
    int current, last = 0, boolean = 0, count = 0, res = 0;

    while(1) {
        if (fscanf(f, "%i", &current) != 1) {break;}
        if (feof(f)) {break;} // если дошли до конца файла
        if (current >= last) {
            count += 1;
            if (boolean) {count += 1;}
        }
        else {
            if (count > res) {
                res = count;
                count = 0;
            }
            boolean = 1;
        }
        last = current;
    }
    return res;
}