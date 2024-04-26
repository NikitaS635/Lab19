#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stddef.h>
typedef struct {
    int **values; // элементы матрицы
    int nRows;    // количество рядов
    int nCols;    // количество столбцов
} matrix;

typedef struct {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);
void freeMemMatrix(matrix *m);
void freeMemMatrices(matrix *ms, int nMatrices);
void inputMatrix(matrix *m);
void inputMatrices(matrix *ms, int nMatrices);
void outputMatrix(matrix m);
void outputMatrices(matrix *ms, int nMatrices);
void swapRows(matrix m, int i1, int i2);
void swapColumns(matrix m, int j1, int j2);
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int));
bool isSquareMatrix(matrix *m);
bool areTwoMatricesEqual(matrix *m1, matrix *m2);
bool isEMatrix(matrix *m);
bool isSymmetricMatrix(matrix *m);
void transposeSquareMatrix(matrix *m);
void transposeMatrix(matrix *m);
position getMinValuePos(matrix m);
position getMaxValuePos(matrix m);
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols);
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);
// Функция для подсчета количества строк с нулевыми элементами
size_t countZeroRows(matrix m, size_t nRows, size_t nCols);
// Функция для вычисления произведения двух матриц
matrix mulMatrices(matrix m1, matrix m2);
int getMax(int *a, int n);
int compareRowsByMaxElement(const void *row1, const void *row2);
// Функция сортировки строк матрицы по максимальному элементу

void sortRowsByMaxElement(matrix m); // Добавленная функция
int getMin(int *a, int n); // Добавленная функция
void sortColsByMinElement(matrix m); // Добавленная функция
int compareColsByMinElement(const void *col1, const void *col2);
// Функция для проверки, все ли суммы элементов в массиве уникальны
bool isUnique(long long *a, int n);

// Функция для вычисления суммы элементов в массиве
long long getSum(int *a, int n);\
//функция для трансп
void transposeIfMatrixHasNotEqualSumOfRows(matrix *m);
bool isMutuallyInverseMatrices(matrix m1, matrix m2);
// Функция для нахождения максимального из двух чисел
int max1(int a, int b);

// Функция для нахождения суммы максимальных элементов псевдодиагоналей матрицы
long long findSumOfMaxesOfPseudoDiagonal(matrix m);
int getMinInArea(matrix m, int startRow, int startCol, int endRow, int endCol);
// Функция для вычисления расстояния от точки до начала координат
float getDistance(int *a, int n);

// Функция для сравнения расстояний до начала координат
int compareDistances(const void *a, const void *b);
// Функция для сортировки точек по расстояниям до начала координат
void sortByDistances(matrix m);

// Функция для сравнения двух long long чисел (для использования в qsort)
int cmp_long_long(const void *pa, const void *pb);

// Функция для подсчета количества уникальных элементов в массиве long long чисел
int countNUnique(long long *a, int n);

// Функция для подсчета количества классов эквивалентных строк по суммам элементов строк матрицы
int countEqClassesByRowsSum(matrix m);

int getNSpecialElement(matrix m);
// Функция для проверки, упорядочена ли строка по неубыванию элементов
bool isNonDescendingSorted(int *a, int n);

// Функция для проверки, упорядочены ли все строки матрицы по неубыванию элементов
bool hasAllNonDescendingRows(matrix m);

// Функция для подсчета числа матриц, строки которых упорядочены по неубыванию элементов
int countNonDescendingRowsMatrices(matrix *ms, int nMatrix);



// Функция для вывода матриц, имеющих максимальное количество нулевых строк
void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix);
int countZeroRows2(matrix m);

double calculateMatrixNorm(matrix matrix);

matrix findMatrixWithMinNorm(matrix *matrices, size_t count);

void printMatrixWithMinNorm(matrix matrix);
// Функция для поиска позиции минимального элемента в матрице
position getLeftMin(matrix m);

// Функция для обмена предпоследней строки матрицы и выбранного столбца
void swapPenultimateRow(matrix m, int colIndex);
#endif // MATRIX_H
