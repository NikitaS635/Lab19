#include <stdio.h>
#include "C:\Users\User2\CLionProjects\untitled\libs\data_structures\matrix\matrix.h"
#include <windows.h>
#include <assert.h>
// Функция для печати позиции элемента
void printPosition(position pos) {
    printf("Строка: %d, Столбец: %d\n", pos.rowIndex, pos.colIndex);
}

// Пример функции-критерия для сортировки строк по сумме элементов
int rowSum(int *row, int nCols) {
    int sum = 0;
    for (int i = 0; i < nCols; i++) {
        sum += row[i];
    }
    return sum;
}
void test_countZeroRows() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    0, 0, 0,
                    0, 0, 1,
                    0, 0, 0,
                    0, 1, 1,
            },
            5, 3
    );
    assert(countZeroRows(m, 5, 3) == 2);
    freeMemMatrix(&m); // Исправлено здесь
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Создание матрицы и ввод элементов
    matrix m = getMemMatrix(3, 3);
    printf("Введите элементы матрицы:\n");
    inputMatrix(&m);

    // Вывод матрицы
    printf("Матрица m:\n");
    outputMatrix(m);

    // Поиск минимального и максимального элементов
    position minPos = getMinValuePos(m);
    position maxPos = getMaxValuePos(m);
    printf("Позиция минимального элемента в матрице 2: ");
    printPosition(minPos);
    printf("Позиция максимального элемента в матрице 2: ");
    printPosition(maxPos);
    // Проверка на квадратную матрицу
    printf("Является ли матрица m квадратной? %s\n", isSquareMatrix(&m) ? "Да" : "Нет");

    // Транспонирование квадратной матрицы
    transposeSquareMatrix(&m);
    printf("Транспонированная матрица m:\n");
    outputMatrix(m);

    // Проверка на единичную матрицу
    printf("Является ли матрица m единичной? %s\n", isEMatrix(&m) ? "Да" : "Нет");

    // Создание массива из двух матриц
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix *ms = createArrayOfMatrixFromArray(values, 2, 3, 3);

    // Вывод массива матриц
    printf("Матрицы из массива:\n");
    outputMatrices(ms, 1);

    // Сортировка строк матрицы по сумме элементов
    insertionSortRowsMatrixByRowCriteria(ms[0], rowSum);
    printf("Матрица 1 отсортированная по сумме строк:\n");
    outputMatrix(ms[0]);

    // Поиск минимального и максимального элементов
    position minPos1 = getMinValuePos(ms[0]);
    position maxPos1 = getMaxValuePos(ms[0]);
    printf("Позиция минимального элемента в матрице 2: ");
    printPosition(minPos1);
    printf("Позиция максимального элемента в матрице 2: ");
    printPosition(maxPos1);
    test_countZeroRows();
    // Освобождение памяти
    freeMemMatrix(&m);
    freeMemMatrices(ms, 2);

    return 0;
}
