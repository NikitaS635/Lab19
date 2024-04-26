#include <stdio.h>
#include "C:\Users\User2\CLionProjects\untitled\libs\data_structures\matrix\matrix.h"
#include <windows.h>
#include <assert.h>
void test1()
{
    matrix matrices[5];

    // Заданные матрицы
    int values1[3][3] = {
            {0, 1, 1},
            {1, 0, 0},
            {0, 0, 0}
    };
    int values2[3][3] = {
            {1, 1, 1},
            {2, 1, 1},
            {1, 1, 1}
    };
    int values3[3][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {4, 7, 0}
    };
    int values4[3][3] = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
    };
    int values5[3][3] = {
            {0, 1, 0},
            {0, 2, 0},
            {0, 3, 0}
    };

    // Заполняем массив матриц
    matrices[0] = createMatrixFromArray(values1, 3, 3);
    matrices[1] = createMatrixFromArray(values2, 3, 3);
    matrices[2] = createMatrixFromArray(values3, 3, 3);
    matrices[3] = createMatrixFromArray(values4, 3, 3);
    matrices[4] = createMatrixFromArray(values5, 3, 3);
    size_t count = sizeof(matrices) / sizeof(matrices[0]);
    // Найдем матрицу с наименьшей нормой
    matrix minNormMatrix = findMatrixWithMinNorm(matrices, count);

    // Выведем матрицу с наименьшей нормой
    printMatrixWithMinNorm(minNormMatrix);
    assert(minNormMatrix.values[0][0] == 0);
    assert(minNormMatrix.values[0][1] == 1);
    assert(minNormMatrix.values[0][2] == 1);

    assert(minNormMatrix.values[1][0] == 1);
    assert(minNormMatrix.values[1][1] == 0);
    assert(minNormMatrix.values[1][2] == 0);

    assert(minNormMatrix.values[2][0] == 0);
    assert(minNormMatrix.values[2][1] == 0);
    assert(minNormMatrix.values[2][2] == 0);
    printf("Тест пройден");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    test1();
    return 0;
}