#include "matrix.h" // Включение заголовочного файла matrix.h
#include <stdio.h> // Включение стандартной библиотеки ввода-вывода
#include <stdlib.h> // Включение стандартной библиотеки управления памятью
#include <stdbool.h> // Включение стандартной библиотеки для работы с булевыми значениями

// Функция для выделения памяти под матрицу с указанным количеством строк и столбцов
matrix getMemMatrix(int nRows, int nCols) {
    matrix m; // Создание переменной типа matrix
    m.nRows = nRows; // Присвоение числа строк
    m.nCols = nCols; // Присвоение числа столбцов
    m.values = (int **)malloc(nRows * sizeof(int *)); // Выделение памяти под указатели на строки
    for (int i = 0; i < nRows; i++) { // Цикл по строкам
        m.values[i] = (int *)malloc(nCols * sizeof(int)); // Выделение памяти под элементы строки
    }
    return m; // Возврат созданной матрицы
}

// Функция для выделения памяти под массив матриц с указанным количеством матриц, строк и столбцов
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *)malloc(nMatrices * sizeof(matrix)); // Выделение памяти под массив матриц
    for (int i = 0; i < nMatrices; i++) { // Цикл по всем матрицам в массиве
        ms[i] = getMemMatrix(nRows, nCols); // Выделение памяти под каждую матрицу
    }
    return ms; // Возврат созданного массива матриц
}

// Функция для освобождения памяти, выделенной под матрицу
void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) { // Цикл по строкам матрицы
        free(m->values[i]); // Освобождение памяти, выделенной под элементы строки
    }
    free(m->values); // Освобождение памяти, выделенной под указатели на строки
}

// Функция для освобождения памяти, выделенной под массив матриц
void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) { // Цикл по всем матрицам в массиве
        freeMemMatrix(&ms[i]); // Освобождение памяти, выделенной под каждую матрицу
    }
    free(ms); // Освобождение памяти, выделенной под массив матриц
}

// Функция для ввода элементов матрицы с клавиатуры
void inputMatrix(matrix *m) {
    printf("Enter elements of the matrix:\n"); // Вывод приглашения для ввода элементов
    for (int i = 0; i < m->nRows; i++) { // Цикл по строкам матрицы
        for (int j = 0; j < m->nCols; j++) { // Цикл по столбцам матрицы
            scanf("%d", &m->values[i][j]); // Считывание элемента с клавиатуры
        }
    }
}

// Функция для ввода нескольких матриц с клавиатуры
void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) { // Цикл по всем матрицам
        printf("Enter elements of matrix %d:\n", i + 1); // Вывод приглашения для ввода элементов матрицы
        inputMatrix(&ms[i]); // Вызов функции для ввода элементов матрицы
    }
}

// Функция для вывода матрицы на экран
void outputMatrix(matrix m) {
    printf("Matrix:\n"); // Вывод заголовка для матрицы
    for (int i = 0; i < m.nRows; i++) { // Цикл по строкам матрицы
        for (int j = 0; j < m.nCols; j++) { // Цикл по столбцам матрицы
            printf("%d ", m.values[i][j]); // Вывод элемента матрицы
        }
        printf("\n"); // Переход на новую строку после каждой строки матрицы
    }
}

// Функция для вывода нескольких матриц на экран
void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) { // Цикл по всем матрицам
        printf("Matrix %d:\n", i + 1); // Вывод заголовка для матрицы
        outputMatrix(ms[i]); // Вызов функции для вывода матрицы на экран
    }
}

// Функция для обмена строк матрицы
void swapRows(matrix m, int i1, int i2) {
    if (i1 < 0 || i2 < 0 || i1 >= m.nRows || i2 >= m.nRows) { // Проверка валидности индексов строк
        printf("Invalid row index.\n"); // Вывод сообщения об ошибке
        return; // Выход из функции
    }
    int *temp = m.values[i1]; // Обмен указателями на строки
    m.values[i1] = m.values[i2]; // Обмен указателями на строки
    m.values[i2] = temp; // Обмен указателями на строки
}

// Функция для обмена столбцов матрицы
void swapColumns(matrix m, int j1, int j2) {
    if (j1 < 0 || j2 < 0 || j1 >= m.nCols || j2 >= m.nCols) { // Проверка валидности индексов столбцов
        printf("Invalid column index.\n"); // Вывод сообщения об ошибке
        return; // Выход из функции
    }
    for (int i = 0; i < m.nRows; i++) { // Цикл по строкам матрицы
        int temp = m.values[i][j1]; // Обмен элементов столбцов
        m.values[i][j1] = m.values[i][j2]; // Обмен элементов столбцов
        m.values[i][j2] = temp; // Обмен элементов столбцов
    }
}

// Функция для сортировки строк матрицы по критерию, заданному пользователем
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    for (int i = 1; i < m.nRows; i++) { // Цикл по строкам матрицы, начиная со второй
        int j = i; // Инициализация переменной j значением i
        while (j > 0 && criteria(m.values[j - 1], m.nCols) > criteria(m.values[j], m.nCols)) { // Цикл для сортировки вставками
            swapRows(m, j - 1, j); // Вызов функции для обмена строк
            j--; // Уменьшение значения j
        }
    }
}

// Функция для сортировки столбцов матрицы по критерию, заданному пользователем
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    for (int i = 0; i < m.nCols; i++) { // Цикл по столбцам матрицы
        int minIndex = i; // Инициализация переменной для индекса минимального элемента
        for (int j = i + 1; j < m.nCols; j++) { // Цикл для поиска минимального элемента в столбце
            if (criteria(m.values[j], m.nRows) < criteria(m.values[minIndex], m.nRows)) { // Сравнение элементов по критерию
                minIndex = j; // Обновление индекса минимального элемента
            }
        }
        if (minIndex != i) { // Проверка, что минимальный элемент не находится на текущей позиции
            swapColumns(m, i, minIndex); // Вызов функции для обмена столбцов
        }
    }
}

// Функция для проверки, является ли матрица квадратной
bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols; // Возвращение результата сравнения количества строк и столбцов
}

// Функция для проверки равенства двух матриц
bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) // Проверка размеров матриц
        return false; // Если размеры матриц не совпадают, то матрицы не равны

    for (int i = 0; i < m1->nRows; i++) { // Цикл по строкам матрицы
        for (int j = 0; j < m1->nCols; j++) { // Цикл по столбцам матрицы
            if (m1->values[i][j] != m2->values[i][j]) // Сравнение элементов матриц
                return false; // Если элементы не равны, то матрицы не равны
        }
    }
    return true; // Если все элементы равны, то матрицы равны
}

// Функция для проверки, является ли матрица единичной
bool isEMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) { // Цикл по строкам матрицы
        for (int j = 0; j < m->nCols; j++) { // Цикл по столбцам матрицы
            if (i == j) { // Если на диагонали
                if (m->values[i][j] != 1) { // Если элемент не равен 1
                    return false; // Матрица не является единичной
                }
            } else { // Если не на диагонали
                if (m->values[i][j] != 0) { // Если элемент не равен 0
                    return false; // Матрица не является единичной
                }
            }
        }
    }
    return true; // Матрица является единичной
}

// Функция для проверки, является ли матрица симметричной
bool isSymmetricMatrix(matrix *m) {
    if (!isSquareMatrix(m)) // Проверка, является ли матрица квадратной
        return false; // Если матрица не квадратная, то она не симметричная

    for (int i = 0; i < m->nRows; i++) { // Цикл по строкам матрицы
        for (int j = i + 1; j < m->nCols; j++) { // Цикл по столбцам, начиная с j = i + 1
            if (m->values[i][j] != m->values[j][i]) // Проверка симметричности элементов
                return false; // Если элементы не симметричны, то матрица не симметрична
        }
    }
    return true; // Если все элементы симметричны, то матрица симметрична
}

// Функция для транспонирования квадратной матрицы
void transposeSquareMatrix(matrix *m) {
    if (!isSquareMatrix(m)) { // Проверка, является ли матрица квадратной
        printf("Matrix is not square.\n"); // Вывод сообщения об ошибке
        return; // Выход из функции
    }

    for (int i = 0; i < m->nRows; i++) { // Цикл по строкам матрицы
        for (int j = i + 1; j < m->nCols; j++) { // Цикл по столбцам, начиная с j = i + 1
            int temp = m->values[i][j]; // Обмен элементов
            m->values[i][j] = m->values[j][i]; // Обмен элементов
            m->values[j][i] = temp; // Обмен элементов
        }
    }
}

// Функция для транспонирования матрицы произвольного размера
void transposeMatrix(matrix *m) {
    int **temp = (int **)malloc(m->nCols * sizeof(int *)); // Выделение памяти под временный массив указателей на строки
    for (int i = 0; i < m->nCols; i++) { // Цикл по столбцам матрицы
        temp[i] = (int *)malloc(m->nRows * sizeof(int)); // Выделение памяти под строки временной матрицы
        for (int j = 0; j < m->nRows; j++) { // Цикл по строкам матрицы
            temp[i][j] = m->values[j][i]; // Копирование элементов в транспонированную матрицу
        }
    }
    for (int i = 0; i < m->nRows; i++) { // Цикл по строкам матрицы
        free(m->values[i]); // Освобождение памяти, выделенной под строки исходной матрицы
    }
    free(m->values); // Освобождение памяти, выделенной под указатели на строки исходной матрицы
    m->values = temp; // Присвоение указателю на массив указателей на строки адреса временного массива
    int tempSize = m->nRows; // Сохранение количества строк во временную переменную
    m->nRows = m->nCols; // Присвоение числа строк числу столбцов
    m->nCols = tempSize; // Присвоение числа столбцов числу строк
}

// Функция для получения позиции минимального элемента матрицы
position getMinValuePos(matrix m) {
    position minPos; // Создание переменной для хранения позиции минимального элемента
    minPos.rowIndex = 0; // Инициализация индекса строки минимального элемента
    minPos.colIndex = 0; // Инициализация индекса столбца минимального элемента
    int minValue = m.values[0][0]; // Инициализация минимального значения
    for (int i = 0; i < m.nRows; i++) { // Цикл по строкам матрицы
        for (int j = 0; j < m.nCols; j++) { // Цикл по столбцам матрицы
            if (m.values[i][j] < minValue) { // Проверка, является ли текущий элемент минимальным
                minValue = m.values[i][j]; // Обновление минимального значения
                minPos.rowIndex = i; // Обновление индекса строки минимального элемента
                minPos.colIndex = j; // Обновление индекса столбца минимального элемента
            }
        }
    }
    return minPos; // Возврат позиции минимального элемента
}

// Функция для получения позиции максимального элемента матрицы
position getMaxValuePos(matrix m) {
    position maxPos; // Создание переменной для хранения позиции максимального элемента
    maxPos.rowIndex = 0; // Инициализация индекса строки максимального элемента
    maxPos.colIndex = 0; // Инициализация индекса столбца максимального элемента
    int maxValue = m.values[0][0]; // Инициализация максимального значения
    for (int i = 0; i < m.nRows; i++) { // Цикл по строкам матрицы
        for (int j = 0; j < m.nCols; j++) { // Цикл по столбцам матрицы
            if (m.values[i][j] > maxValue) { // Проверка, является ли текущий элемент максимальным
                maxValue = m.values[i][j]; // Обновление максимального значения
                maxPos.rowIndex = i; // Обновление индекса строки максимального элемента
                maxPos.colIndex = j; // Обновление индекса столбца максимального элемента
            }
        }
    }
    return maxPos; // Возврат позиции максимального элемента
}

// Функция для создания матрицы из одномерного массива
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {
    matrix m = getMemMatrix(nRows, nCols); // Выделение памяти под матрицу
    for (int i = 0; i < nRows; i++) { // Цикл по строкам матрицы
        for (int j = 0; j < nCols; j++) { // Цикл по столбцам матрицы
            m.values[i][j] = a[i * nCols + j]; // Заполнение элементов матрицы значениями из одномерного массива
        }
    }
    return m; // Возврат созданной матрицы
}

// Функция для создания массива матриц из одномерного массива
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols); // Выделение памяти под массив матриц
    int l = 0; // Инициализация счётчика элементов в одномерном массиве
    for (size_t k = 0; k < nMatrices; k++) { // Цикл по всем матрицам в массиве
        for (size_t i = 0; i < nRows; i++) { // Цикл по строкам матрицы
            for (size_t j = 0; j < nCols; j++) { // Цикл по столбцам матрицы
                ms[k].values[i][j] = values[l++]; // Заполнение элементов матрицы значениями из одномерного массива
            }
        }
    }
    return ms; // Возврат созданного массива матриц
}
// Функция для подсчета количества строк с нулевыми элементами
size_t countZeroRows(matrix m, size_t nRows, size_t nCols) {
    size_t zeroRowCount = 0; // Счетчик строк с нулевыми элементами

    // Перебираем строки матрицы
    for (size_t i = 0; i < nRows; ++i) {
        bool isZeroRow = true; // Предполагаем, что текущая строка состоит только из нулей

        // Перебираем элементы в текущей строке
        for (size_t j = 0; j < nCols; ++j) {
            // Если встречаем ненулевой элемент, текущая строка не является нулевой
            if (m.values[i][j] != 0) {
                isZeroRow = false;
                break;
            }
        }

        // Если строка состоит только из нулей, увеличиваем счетчик
        if (isZeroRow) {
            ++zeroRowCount;
        }
    }

    return zeroRowCount;
}
