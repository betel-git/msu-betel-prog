#ifndef HEADER
#define HEADER

#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

unsigned int * ReadArrayCnt(FILE *f, long long int *size, int *errcode);

//void QuickBitSort(long long int n, unsigned int* a, int bitIndex, int ascending);

//int QuickBitSortPartition(long long int n, unsigned int* a, int ibit, int asceding);

void Swap(unsigned int* a, unsigned int* b);

//void swap(unsigned int *a, unsigned int *b);

//int get_kth_bit(unsigned int num, int k);

//void bit_quick_sort(unsigned int arr[], int low, int high, int k);

bool TestBit(int x, int k);

bool TestSort(long long int n, unsigned int *arr);

//int QuickBitSortPartition(unsigned int *arr, int low, int high, int asceding);

//void QuickSort(unsigned int *arr, int low, int high, int asceding);

void QuickBitSort(long long int n, unsigned int *a, int bit, int asceding);

long long int QuickBitSortPartition(long long int n, unsigned int *a, int ibit, int asceding);

//void QuickBitSort2(long long int n, unsigned int* a,int asceding);

//long long int QuickBitSortPartition2(long long int n, unsigned int *a, int asceding);

int CmpInt(const void *a, const void *b);

#endif