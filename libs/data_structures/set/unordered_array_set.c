#include "unordered_array_set.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
unordered_array_set unordered_array_set_create(size_t capacity) {
    unordered_array_set set;
    set.data = malloc(capacity * sizeof(int));
    if (set.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    set.size = 0;
    set.capacity = capacity;
    return set;
}

unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; ++i) {
        unordered_array_set_insert(&set, a[i]);
    }
    return set;
}

size_t unordered_array_set_in(unordered_array_set set, int value) {
    for (size_t i = 0; i < set.size; ++i) {
        if (set.data[i] == value) {
            return i;
        }
    }
    return set.size;
}

size_t unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    for (size_t i = 0; i < subset.size; ++i) {
        if (unordered_array_set_in(set, subset.data[i]) == set.size) {
            return 0;
        }
    }
    return 1;
}

bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }
    for (size_t i = 0; i < set1.size; ++i) {
        if (unordered_array_set_in(set2, set1.data[i]) == set2.size) {
            return false;
        }
    }
    return true;
}

void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    if (set->size >= set->capacity) {
        size_t new_capacity = set->capacity + 5; // Увеличиваем емкость на 5 элементов
        int *new_data = realloc(set->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        set->data = new_data;
        set->capacity = new_capacity;
    }
}


bool unordered_array_set_insert(unordered_array_set *set, int element) {
    // Проверяем, не содержит ли уже множество данный элемент
    for (size_t i = 0; i < set->size; ++i) {
        if (set->data[i] == element) {
            return false;  // Элемент уже есть, не добавляем его
        }
    }

    // Если элемента еще нет, добавляем его в множество
    if (set->size < set->capacity) {
        set->data[set->size++] = element;
        return true;
    } else {
        // Добавляем элемент, увеличивая размер массива
        set->capacity *= 2;
        set->data = realloc(set->data, set->capacity * sizeof(int));
        if (!set->data) {
            // Обработка ошибки выделения памяти
            return false;
        }
        set->data[set->size++] = element;
        return true;
    }
}




void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t pos = unordered_array_set_in(*set, value);
    if (pos < set->size) {
        for (size_t i = pos; i < set->size - 1; ++i) {
            set->data[i] = set->data[i + 1];
        }
        set->size--;
    }
}

unordered_array_set unordered_array_set_union(const unordered_array_set set1, const unordered_array_set set2) {
    unordered_array_set result = unordered_array_set_create(set1.size + set2.size);

    // Копируем элементы из первого множества в результирующее
    for (size_t i = 0; i < set1.size; ++i) {
        unordered_array_set_insert(&result, set1.data[i]);
    }

    // Копируем элементы из второго множества в результирующее
    for (size_t i = 0; i < set2.size; ++i) {
        unordered_array_set_insert(&result, set2.data[i]);
    }

    return result;
}



unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set result = unordered_array_set_create(0);
    for (size_t i = 0; i < set1.size; ++i) {
        if (unordered_array_set_in(set2, set1.data[i]) != set2.size) {
            unordered_array_set_insert(&result, set1.data[i]);
        }
    }
    return result;
}

unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set result = unordered_array_set_create(0);
    for (size_t i = 0; i < set1.size; ++i) {
        if (unordered_array_set_in(set2, set1.data[i]) == set2.size) {
            unordered_array_set_insert(&result, set1.data[i]);
        }
    }
    return result;
}

unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set diff1 = unordered_array_set_difference(set1, set2);
    unordered_array_set diff2 = unordered_array_set_difference(set2, set1);
    unordered_array_set result = unordered_array_set_union(diff1, diff2);
    unordered_array_set_delete(diff1);
    unordered_array_set_delete(diff2);
    return result;
}

void unordered_array_set_print(unordered_array_set set) {
    printf("{ ");
    for (size_t i = 0; i < set.size; ++i) {
        printf("%d ", set.data[i]);
    }
    printf("}\n");
}

void unordered_array_set_delete(unordered_array_set set) {
    free(set.data);
}
