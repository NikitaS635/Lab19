#include "sorttime.h"
#include "string.h"
#define RADIX 256 // Основание системы счисления



// Структура для хранения статистики сортировки (включая количество операций сравнения и время выполнения)
typedef struct SortStats {
    char sortName[64]; // имя сортировки
    char generatorName[64]; // имя генератора
    size_t size; // размер массива
    unsigned long long comparisons; // количество операций сравнения
    double time; // время выполнения
} SortStats;

// Функция для сортировки массива и подсчета количества операций сравнения
void getComparisonCount(void (*sortFunc)(int *, size_t, unsigned long long *), int *a, size_t n, unsigned long long *comparisons) {
    if (sortFunc == NULL || a == NULL) {
        printf("Error: Invalid function pointer or array pointer\n");
        return;
    }

    *comparisons = 0; // Обнуляем счетчик операций сравнения

    // Создаем временный массив для сортировки
    int *tempArray = (int *)malloc(n * sizeof(int));
    if (tempArray == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    // Копируем исходный массив для сортировки
    memcpy(tempArray, a, n * sizeof(int));

    // Сортировка временного массива с подсчетом операций сравнения
    sortFunc(tempArray, n, comparisons);

    free(tempArray); // Освобождаем временный массив
}

// Пример функции сортировки: сортировка обменом (пузырьковая)
void bubbleSort(int *a, size_t n, unsigned long long *comparisons) {
    *comparisons = 0; // Обнуляем счетчик операций сравнения

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                (*comparisons)++;
            }
        }
    }
}

// Функция для получения значения байта по определенному разряду
int getByte(int num, int byteIndex) {
    return (num >> (byteIndex * 8)) & 0xFF;
}



// Пример функции сортировки: сортировка выбором
void selectionSort(int *a, size_t n, unsigned long long *comparisons) {
    *comparisons = 0; // Обнуляем счетчик операций сравнения

    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
            (*comparisons)++;
        }
        int temp = a[i];
        a[i] = a[min_idx];
        a[min_idx] = temp;
    }
}

// Пример функции сортировки: сортировка вставками
void insertionSort(int *a, size_t n, unsigned long long *comparisons) {
    *comparisons = 0; // Обнуляем счетчик операций сравнения

    for (size_t i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
            (*comparisons)++;
        }
        a[j + 1] = key;
    }
}

// Функция генерации случайного массива
void generateRandomArray(int *a, size_t n) {
    srand(time(NULL));
    for (size_t i = 0; i < n; i++) {
        a[i] = rand() % 25; // предполагаем диапазон значений от 0 до 99
    }
}

// Функция генерации массива в порядке убывания
void generateOrderedBackwards(int *a, size_t n) {
    for (size_t i = 0; i < n; i++) {
        a[i] = n - i - 1;
    }
}
// Реализация алгоритма сортировки расческой
void combSort(int *a, size_t n, unsigned long long *comparisons) {
    *comparisons = 0; // Обнуляем счетчик операций сравнения

    int gap = n;
    float shrink = 1.3;
    bool sorted = false;

    while (!sorted) {
        // Вычисляем новый размер промежутка
        gap = (int)(gap / shrink);
        if (gap > 1) {
            sorted = false;
        } else {
            gap = 1;
            sorted = true;
        }

        // Проходим по массиву и меняем элементы
        for (size_t i = 0; i + gap < n; i++) {
            if (a[i] > a[i + gap]) {
                int temp = a[i];
                a[i] = a[i + gap];
                a[i + gap] = temp;
                sorted = false;
                (*comparisons)++;
            }
        }
    }
}
// Реализация алгоритма сортировки Шелла
void shellSort(int *a, size_t n, unsigned long long *comparisons) {
    *comparisons = 0; // Обнуляем счетчик операций сравнения

    // Выбираем начальный интервал
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Проходим по подмассивам
        for (int i = gap; i < n; i++) {
            // Сортировка вставками для подмассива
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
                a[j] = a[j - gap];
                (*comparisons)++;
            }
            a[j] = temp;
        }
    }
}
// Реализация цифровой сортировки для положительных чисел
void radixSortPositive(int *a, size_t n, unsigned long long *comparisons) {
    *comparisons = 0; // Обнуляем счетчик операций сравнения

    // Находим максимальное число в массиве
    int maxNum = a[0];
    for (size_t i = 1; i < n; ++i) {
        if (a[i] > maxNum) {
            maxNum = a[i];
        }
    }

    // Сортировка по каждому байту числа
    for (int byteIndex = 0; byteIndex < sizeof(int); ++byteIndex) {
        // Создаем временный массив для подсчета частот
        int count[RADIX] = {0};

        // Подсчитываем частоту появления каждого байта
        for (size_t i = 0; i < n; ++i) {
            int byteValue = getByte(a[i], byteIndex);
            count[byteValue]++;
        }

        // Вычисляем аккумулятивные суммы
        for (int i = 1; i < RADIX; ++i) {
            count[i] += count[i - 1];
        }

        // Формируем отсортированный массив
        int *sortedArray = (int *)malloc(n * sizeof(int));
        if (sortedArray == NULL) {
            printf("Error: Memory allocation failed\n");
            return;
        }

        for (int i = n - 1; i >= 0; --i) {
            int byteValue = getByte(a[i], byteIndex);
            sortedArray[--count[byteValue]] = a[i];
        }

        // Копируем отсортированный массив обратно в исходный
        memcpy(a, sortedArray, n * sizeof(int));
        free(sortedArray);
    }
}


double getTime(void (*sortFunc)(int *, size_t, unsigned long long *), int *a, size_t n, unsigned long long *comparisons) {
    if (sortFunc == NULL || a == NULL) {
        printf("Error: Invalid function pointer or array pointer\n");
        return -1.0; // Вернем отрицательное значение как признак ошибки
    }

    // Создаем временный массив для сортировки
    int *tempArray = (int *)malloc(n * sizeof(int));
    if (tempArray == NULL) {
        printf("Error: Memory allocation failed\n");
        return -1.0; // Вернем отрицательное значение как признак ошибки
    }
    // Копируем исходный массив для сортировки
    memcpy(tempArray, a, n * sizeof(int));

    clock_t start_time = clock();
    sortFunc(tempArray, n, comparisons); // Сортировка временного массива
    clock_t end_time = clock();

    free(tempArray); // Освобождаем временный массив

    return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
// Определение структуры для функции сортировки
typedef struct SortFunc {
    void (*sort)(int *, size_t, unsigned long long *comparisons); // указатель на функцию сортировки
    char name[64]; // имя сортировки
} SortFunc;

// Определение структуры для функции генерации массива
typedef struct GeneratingFunc {
    void (*generate)(int *, size_t); // указатель на функцию генерации массива
    char name[64]; // имя генератора
} GeneratingFunc;
// Функция для проведения эксперимента по временным замерам
void timeExperiment() {
    // Описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {bubbleSort, "bubbleSort"},
            {combSort, "combSort"},
            {shellSort, "shellSort"},
            {radixSortPositive, "radixSortPositive"},


    };
    const unsigned FUNCS_N = sizeof(sorts) / sizeof(sorts[0]);

    // Описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            {generateRandomArray, "random"},
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = sizeof(generatingFuncs) / sizeof(generatingFuncs[0]);

    // Запись статистики в файл
    FILE *file = fopen("sorting_results.csv", "w");
    if (file == NULL) {
        printf("Error: Unable to open file for writing\n");
        return;
    }
    fprintf(file, "Sort Algorithm, Generator, Array Size, Comparisons, Time\n");

    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("------------------------------\n");
        printf("Size: %zu\n", size);
        int *tempArray = malloc(size * sizeof(int)); // Динамическое выделение памяти
        if (tempArray == NULL) {
            printf("Error: Memory allocation failed\n");
            fclose(file);
            return;
        }
        for (size_t i = 0; i < FUNCS_N; i++) {
            for (size_t j = 0; j < CASES_N; j++) {
                // Генерация случайного массива
                generatingFuncs[j].generate(tempArray, size);
                // Выполнение сортировки и подсчет операций сравнения
                unsigned long long comparisons;
                getComparisonCount(sorts[i].sort, tempArray, size, &comparisons);
                // Запись данных в файл
                double time = getTime(sorts[i].sort, tempArray, size, &comparisons);
                fprintf(file, "%s, %s, %zu, %llu, %.6f\n", sorts[i].name, generatingFuncs[j].name, size, comparisons, time);
                printf( "%s, %s, %zu, %llu, %.6f\n", sorts[i].name, generatingFuncs[j].name, size, comparisons, time);
            }
        }
        free(tempArray); // Освобождаем память
        printf("\n");
    }

    fclose(file); // Закрываем файл
}
