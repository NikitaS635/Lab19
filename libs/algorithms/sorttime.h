#ifndef SORTTIME_H
#define SORTTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>



// Прототипы функций
double getTime(void (*sortFunc)(int *, size_t, unsigned long long *), int *a, size_t n, unsigned long long *comparisons);
void timeExperiment();

// Прототипы функций сортировок
void selectionSort(int *a, size_t n, unsigned long long *comparisons);
void insertionSort(int *a, size_t n, unsigned long long *comparisons);
void bubbleSort(int *a, size_t n, unsigned long long *comparisons);
void combSort(int *a, size_t n, unsigned long long *comparisons);
void shellSort(int *a, size_t n, unsigned long long *comparisons);
void radixSortPositive(int *a, size_t n, unsigned long long *comparisons);

// Функция для получения значения байта по определенному разряду
int getByte(int num, int byteIndex);

#endif // SORTTIME_H
