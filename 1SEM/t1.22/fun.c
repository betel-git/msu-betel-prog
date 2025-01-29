#include "greatestsequence.h"
#include <limits.h>

double GreatestSequence(FILE *f) {
    int current, last = INT_MIN, boolean = 0, count = 0, res = 0;

    while(1) {
        if (fscanf(f, "%i", &current) != 1) {
            if (count > res) {
                res = count;
                count = 0;
            }
            break;
        }
        //if (feof(f)) {break;} // если дошли до конца файла
        if (current >= last) {
            count += 1;
            if (boolean) {
                count += 1;
                boolean = 0;
            }
        }
        else {
            if (count > res) {
                res = count;
                count = 0;
            }
            boolean = 1;
        }
        last = current;
        fprintf(stdout, "current %i\n", current);
        fprintf(stdout, "count %i\n", count);
    }
    return res;
}