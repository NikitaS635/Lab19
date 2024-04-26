#include "matrix.h" // Включение заголовочного файла matrix.h
#include <stdio.h> // Включение стандартной библиотеки ввода-вывода
#include <stdlib.h> // Включение стандартной библиотеки управления памятью
#include <stdbool.h> // Включение стандартной библиотеки для работы с булевыми значениями
#include <math.h>
#define MAX_SIZE 100
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

// Функция для вычисления произведения двух матриц
matrix mulMatrices(matrix m1, matrix m2) {
    // Проверяем возможность умножения матриц
    if (m1.nCols != m2.nRows) {
        printf("Error: Matrices dimensions are incompatible for multiplication\n");
        exit(EXIT_FAILURE);
    }

    // Создаем матрицу-результат с размерами, соответствующими размерам произведения
    matrix result = getMemMatrix(m1.nRows, m2.nCols);

    // Вычисляем элементы произведения матриц
    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return result;
}

// Функция для получения максимального элемента в строке
int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

// Функция сравнения для сортировки строк матрицы по максимальному элементу
int compareRowsByMaxElement(const void *row1, const void *row2) {
    const int *r1 = *(const int **)row1;
    const int *r2 = *(const int **)row2;
    int max1 = getMax(r1, sizeof(r1) / sizeof(r1[0]));
    int max2 = getMax(r2, sizeof(r2) / sizeof(r2[0]));
    return max1 - max2;
}
// Функция сортировки строк матрицы по максимальному элементу
void sortRowsByMaxElement(matrix m) {
    qsort(m.values, m.nRows, sizeof(m.values[0]), compareRowsByMaxElement);
}


// Функция для получения минимального элемента в столбце
int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

// Функция сравнения для сортировки столбцов матрицы по минимальному элементу
int compareColsByMinElement(const void *col1, const void *col2) {
    const int *c1 = *(const int **)col1;
    const int *c2 = *(const int **)col2;
    int min1 = getMin(c1, sizeof(c1) / sizeof(c1[0]));
    int min2 = getMin(c2, sizeof(c2) / sizeof(c2[0]));

    if (min1 != min2) {
        return min1 - min2; // Сортируем по минимальному элементу
    } else {
        // Если минимальные элементы равны, сравниваем индексы столбцов
        return c2[0] - c1[0]; // Изменено для правильного порядка
    }
}



// Функция сортировки столбцов матрицы по минимальному элементу
void sortColsByMinElement(matrix m) {
    int nCols = m.nCols;
    int nRows = m.nRows;
    // Создаем массив указателей на столбцы
    int **cols = malloc(nCols * sizeof(int *));
    if (cols == NULL) {
        // Обработка ошибки выделения памяти
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Заполняем массив указателей
    for (int j = 0; j < nCols; ++j) {
        cols[j] = malloc(nRows * sizeof(int));
        if (cols[j] == NULL) {
            // Обработка ошибки выделения памяти
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nRows; ++i) {
            cols[j][i] = m.values[i][j];
        }
    }
    // Сортируем массив указателей на столбцы
    qsort(cols, nCols, sizeof(cols[0]), compareColsByMinElement);
    // Копируем отсортированные столбцы обратно в матрицу
    for (int j = 0; j < nCols; ++j) {
        for (int i = 0; i < nRows; ++i) {
            m.values[i][j] = cols[j][i];
        }
    }
    // Освобождаем память, выделенную для массива указателей
    for (int j = 0; j < nCols; ++j) {
        free(cols[j]);
    }
    free(cols);
}

// Функция для проверки, все ли суммы элементов в массиве уникальны
bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                return false; // Найдены две равные суммы, массив не уникальный
            }
        }
    }
    return true; // Все суммы уникальны
}

// Функция для вычисления суммы элементов в массиве
long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    return sum;
}


// Функция для транспонирования матрицы, если суммы элементов строк уникальны

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    int n = m->nRows;

    // Выделяем память для массива сумм строк матрицы
    long long *sums = malloc(n * sizeof(long long));
    if (sums == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Вычисляем суммы элементов в строках матрицы
    for (int i = 0; i < n; ++i) {
        sums[i] = getSum(m->values[i], n);
    }

    // Проверяем, все ли суммы уникальны
    if (isUnique(sums, n)) {
        transposeMatrix(m); // Транспонируем матрицу
    }

    // Освобождаем выделенную память
    free(sums);
}

// Функция для проверки, являются ли две матрицы взаимно обратными
bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    // Проверяем, являются ли матрицы квадратными
    if (!isSquareMatrix(&m1) || !isSquareMatrix(&m2)) {
        return false;
    }

    // Проверяем, имеют ли матрицы одинаковый порядок
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols) {
        return false;
    }

    // Вычисляем произведение матрицы m1 на матрицу m2
    matrix product = mulMatrices(m1, m2);

    // Создаем единичную матрицу того же размера, что и произведение матриц
    matrix identity = getMemMatrix(product.nRows, product.nCols);
    for (int i = 0; i < product.nRows; ++i) {
        for (int j = 0; j < product.nCols; ++j) {
            if (i == j) {
                identity.values[i][j] = 1;
            } else {
                identity.values[i][j] = 0;
            }
        }
    }

    // Проверяем, равно ли произведение матриц единичной матрице
    bool result = areTwoMatricesEqual(&product, &identity);

    // Освобождаем память, выделенную для произведения и единичной матриц
    freeMemMatrix(&product);
    freeMemMatrix(&identity);

    return result;
}

// Функция для нахождения максимального из двух чисел
int max1(int a, int b) {
    return (a > b) ? a : b;
}

// Функция для нахождения суммы максимальных элементов псевдодиагоналей матрицы
long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int nRows = m.nRows;
    int nCols = m.nCols;

    // Вычисляем размерность массива для хранения максимальных элементов псевдодиагоналей
    int maxSize = nRows + nCols - 1;
    int pseudoDiagonalMaxes[maxSize];

    // Инициализируем максимальные элементы значением INT_MIN
    for (int i = 0; i < maxSize; ++i) {
        pseudoDiagonalMaxes[i] = INT_MIN;
    }

    // Проходим по матрице и обновляем максимальные элементы псевдодиагоналей
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            // Проверяем, не находится ли элемент на главной диагонали
            if (i != j) {
                int pseudoDiagonalIndex = j - i + (nRows - 1);
                pseudoDiagonalMaxes[pseudoDiagonalIndex] = max1(pseudoDiagonalMaxes[pseudoDiagonalIndex], m.values[i][j]);
            }
        }
    }

    // Вычисляем сумму максимальных элементов псевдодиагоналей
    long long sum = 0;
    for (int i = 0; i < maxSize; ++i) {
        if (pseudoDiagonalMaxes[i] != INT_MIN) {
            sum += pseudoDiagonalMaxes[i];
        }
    }

    return sum;
}
// Функция для нахождения минимального элемента в указанной области матрицы
int getMinInArea(matrix m, int startRow, int startCol, int endRow, int endCol) {
    int min = INT_MAX; // Начальное значение минимального элемента

    // Проходим по всем элементам в указанной области
    for (int i = startRow; i <= endRow; ++i) {
        for (int j = startCol; j <= endCol; ++j) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
            }
        }
    }

    return min;
}

// Функция для вычисления расстояния от точки до начала координат
float getDistance(int *a, int n) {
    float sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += a[i] * a[i];
    }
    return sqrt(sum);
}

// Функция для сравнения расстояний до начала координат
int compareDistances(const void *a, const void *b) {
    float distanceA = getDistance(*(int **)a, 3); // Предполагается, что размерность точек 3
    float distanceB = getDistance(*(int **)b, 3);
    if (distanceA < distanceB) return -1;
    if (distanceA > distanceB) return 1;
    return 0;
}

// Функция для сортировки точек по расстояниям до начала координат
void sortByDistances(matrix m) {
    qsort(m.values, m.nRows, sizeof(int *), compareDistances);
}

// Функция для сравнения двух long long чисел (для использования в qsort)
int cmp_long_long(const void *pa, const void *pb) {
    long long a = *(const long long *)pa;
    long long b = *(const long long *)pb;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// Функция для подсчета количества уникальных элементов в массиве long long чисел
int countNUnique(long long *a, int n) {
    int count = 1; // Первый элемент всегда уникальный
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[i - 1]) {
            count++;
        }
    }
    return count;
}

// Функция для подсчета количества классов эквивалентных строк по суммам элементов строк матрицы
int countEqClassesByRowsSum(matrix m) {
    long long *sums = (long long *)malloc(m.nRows * sizeof(long long));
    if (sums == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Вычисляем суммы элементов каждой строки
    for (int i = 0; i < m.nRows; ++i) {
        sums[i] = 0;
        for (int j = 0; j < m.nCols; ++j) {
            sums[i] += m.values[i][j];
        }
    }

    // Сортируем массив сумм
    qsort(sums, m.nRows, sizeof(long long), cmp_long_long);

    // Подсчитываем количество уникальных сумм (классов эквивалентности строк)
    int uniqueCount = countNUnique(sums, m.nRows);

    free(sums); // Освобождаем выделенную память
    return uniqueCount;
}

// Функция для нахождения количества "особых" элементов в матрице
int getNSpecialElement(matrix m) {
    int count = 0; // Счетчик "особых" элементов

    // Проходим по каждому столбцу матрицы
    for (int j = 0; j < m.nCols; ++j) {
        // Находим сумму всех элементов столбца
        int columnSum = 0;
        for (int i = 0; i < m.nRows; ++i) {
            columnSum += m.values[i][j];
        }

        // Проходим по каждому элементу столбца и проверяем, является ли он "особым"
        for (int i = 0; i < m.nRows; ++i) {
            if (m.values[i][j] > columnSum - m.values[i][j]) {
                count++; // Увеличиваем счетчик, если элемент "особый"
            }
        }
    }

    return count; // Возвращаем количество "особых" элементов
}

// Функция для проверки, упорядочена ли строка по неубыванию элементов
bool isNonDescendingSorted(int *a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

// Функция для проверки, упорядочены ли все строки матрицы по неубыванию элементов
bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        if (!isNonDescendingSorted(m.values[i], m.nCols)) {
            return false;
        }
    }
    return true;
}

// Функция для подсчета числа матриц, строки которых упорядочены по неубыванию элементов
int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; ++i) {
        if (hasAllNonDescendingRows(ms[i])) {
            count++;
        }
    }
    return count;
}


// Функция для подсчета количества нулевых строк в матрице
int countZeroRows2(matrix m) {
    int count = 0;
    for (size_t i = 0; i < m.nRows; ++i) {
        bool isZeroRow = true;
        for (size_t j = 0; j < m.nCols; ++j) {
            if (m.values[i][j] != 0) {
                isZeroRow = false;
                break;
            }
        }
        if (isZeroRow) {
            count++;
        }
    }
    return count;
}

// Функция для вывода матриц, имеющих максимальное количество нулевых строк
void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int maxZeroRows = 0;
    for (int i = 0; i < nMatrix; ++i) {
        int zeroRowCount = countZeroRows2(ms[i]);
        if (zeroRowCount > maxZeroRows) {
            maxZeroRows = zeroRowCount;
        }
    }
    for (int i = 0; i < nMatrix; ++i) {
        if (countZeroRows2(ms[i]) == maxZeroRows) {
            printf("Matrix %d:\n", i + 1);
            for (size_t j = 0; j < ms[i].nRows; ++j) {
                for (size_t k = 0; k < ms[i].nCols; ++k) {
                    printf("%d ", ms[i].values[j][k]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}

double calculateMatrixNorm(matrix matrix) {
    double maxAbsoluteValue = 0.0;
    for (int i = 0; i < matrix.nRows; ++i) {
        for (int j = 0; j < matrix.nCols; ++j) {
            double absoluteValue = fabs(matrix.values[i][j]);
            if (absoluteValue > maxAbsoluteValue) {
                maxAbsoluteValue = absoluteValue;
            }
        }
    }
    return maxAbsoluteValue;
}

matrix findMatrixWithMinNorm(matrix *matrices, size_t count) {
    double minNorm = calculateMatrixNorm(matrices[0]);
    size_t index = 0;
    for (size_t i = 1; i < count; ++i) {
        double norm = calculateMatrixNorm(matrices[i]);
        if (norm < minNorm) {
            minNorm = norm;
            index = i;
        }
    }
    return matrices[index];
}

void printMatrixWithMinNorm(matrix matrix) {
    printf("Matrix with minimum norm:\n");
    for (int i = 0; i < matrix.nRows; ++i) {
        for (int j = 0; j < matrix.nCols; ++j) {
            printf("%d ", matrix.values[i][j]);
        }
        printf("\n");
    }
}

// Функция для поиска позиции минимального элемента в матрице
position getLeftMin(matrix m) {
    position pos;
    pos.rowIndex = -1;
    pos.colIndex = -1;

    int minElement = INT_MAX;

    // Перебор элементов матрицы
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < minElement) {
                minElement = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }
        }
    }

    return pos;
}

// Функция для обмена предпоследней строки матрицы и выбранного столбца
void swapPenultimateRow(matrix m, int colIndex) {
    if (m.nRows < 2 || colIndex < 0 || colIndex >= m.nCols) {
        printf("Некорректные параметры для обмена строк.\n");
        return;
    }

    int temp[m.nCols]; // Временный массив для хранения столбца

    // Сохраняем выбранный столбец во временный массив
    for (int i = 0; i < m.nRows; i++) {
        temp[i] = m.values[i][colIndex];
    }

    // Заменяем предпоследнюю строку выбранным столбцом
    for (int j = 0; j < m.nCols; j++) {
        m.values[m.nRows - 2][j] = temp[j];
    }
}
