// Сортировка слиянием с доп. памятью - итерационный восходящий вариант
#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#define EPS 1e-16

void Prn(const double *a, int n);

void Sort1(double *a, int n);
void Sort2(double *a, const size_t n, int (*Compare) (double, double));
void Sort3(void *a, size_t n, size_t elem_length, int (*cmp) (const void *, const void *));

void Merge_1(double *a, int n, double *b, int m, double *c);
void Merge_2(double *a, size_t n, double *b, size_t m, double *c, int (*Compare) (double, double));
void Merge_3(void *a, size_t n, void *b, size_t m, void *c, size_t elem_length);

int Compare(double x, double y);
int cmp(const void *x, const void *y);

void Change_mean(char *a, char *b, int elem_length);   
void Change_elem(char *a, char *b, int elem_length);

void copy(const double *a, double *b, size_t n);
void Copy(void *a1, void *a2, size_t, size_t elem_length);

int Cnt(double *a, int n);
