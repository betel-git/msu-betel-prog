// 
//  пример простейшего кода для обработки массива       
// 

// прототипы библиотечных функций
// здесь не требуются

// прототипы функций
#include "minmax2.h"

// определения функций

void MinMax (double *x, size_t size, double *pmin, double *pmax)
{
   size_t i;
   *pmin = *pmax = x[0];
   for (i = 1; i<size; i++) 
   {
      if ( *pmin > x[i]) { *pmin = x[i]; }
      if ( *pmax < x[i]) { *pmax = x[i]; }
   }                     
}















