#include "ordered_array_set.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

ordered_array_set ordered_array_set_create(size_t capacity) {
    ordered_array_set set;
    set.capacity = capacity;
    set.size = 0;
    set.data = (int *)malloc(capacity * sizeof(int));
    assert(set.data != NULL);
    return set;
}

ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    ordered_array_set set;
    set.capacity = size;
    set.size = size;
    set.data = (int *)malloc(size * sizeof(int));
    assert(set.data != NULL);
    for (size_t i = 0; i < size; ++i) {
        set.data[i] = a[i];
    }
    return set;
}

size_t ordered_array_set_in(ordered_array_set *set, int value) {
    for (size_t i = 0; i < set->size; ++i) {
        if (set->data[i] == value) {
            return i;
        }
    }
    return set->size; // Возвращаем размер множества, если элемент не найден
}

bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }
    for (size_t i = 0; i < set1.size; ++i) {
        if (set1.data[i] != set2.data[i]) {
            return false;
        }
    }
    return true;
}

bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set) {
    if (subset.size > set.size) {
        return false;
    }
    size_t i = 0, j = 0;
    while (i < subset.size && j < set.size) {
        if (subset.data[i] < set.data[j]) {
            return false;
        } else if (subset.data[i] == set.data[j]) {
            ++i;
        }
        ++j;
    }
    return i == subset.size;
}

void ordered_array_set_isAbleAppend(ordered_array_set *set) {
    if (set->size >= set->capacity) {
        size_t new_capacity = set->capacity * 2; // Удваиваем текущую емкость
        int *new_data = realloc(set->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        set->data = new_data;
        set->capacity = new_capacity;
    }
}

void ordered_array_set_insert(ordered_array_set *set, int value) {
    ordered_array_set_isAbleAppend(set);
    set->data[set->size++] = value;
}

void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    size_t index = ordered_array_set_in(set, value);
    if (index < set->size) {
        for (size_t i = index; i < set->size - 1; ++i) {
            set->data[i] = set->data[i + 1];
        }
        --set->size;
    }
}

ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.size + set2.size);
    for (size_t i = 0; i < set1.size; ++i) {
        ordered_array_set_insert(&result, set1.data[i]);
    }
    for (size_t i = 0; i < set2.size; ++i) {
        ordered_array_set_insert(&result, set2.data[i]);
    }
    return result;
}

ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.size < set2.size ? set1.size : set2.size);
    size_t i = 0, j = 0;
    while (i < set1.size && j < set2.size) {
        if (set1.data[i] < set2.data[j]) {
            ++i;
        } else if (set1.data[i] == set2.data[j]) {
            ordered_array_set_insert(&result, set1.data[i]);
            ++i;
            ++j;
        } else {
            ++j;
        }
    }
    return result;
}

ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.size);
    size_t i = 0, j = 0;
    while (i < set1.size && j < set2.size) {
        if (set1.data[i] < set2.data[j]) {
            ordered_array_set_insert(&result, set1.data[i]);
            ++i;
        } else if (set1.data[i] == set2.data[j]) {
            ++i;
            ++j;
        } else {
            ++j;
        }
    }
    while (i < set1.size) {
        ordered_array_set_insert(&result, set1.data[i]);
        ++i;
    }
    return result;
}

ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set diff1 = ordered_array_set_difference(set1, set2);
    ordered_array_set diff2 = ordered_array_set_difference(set2, set1);
    ordered_array_set result = ordered_array_set_union(diff1, diff2);
    ordered_array_set_delete(&diff1);
    ordered_array_set_delete(&diff2);
    return result;
}

ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet) {
    ordered_array_set diff = ordered_array_set_difference(universumSet, set);
    return diff;
}

void ordered_array_set_print(ordered_array_set set) {
    printf("Множество: { ");
    for (size_t i = 0; i < set.size; ++i) {
        printf("%d ", set.data[i]);
    }
    printf("}\n");
}

void ordered_array_set_delete(ordered_array_set *set) {
    free(set->data);
    set->data = NULL;
    set->size = 0;
    set->capacity = 0;
}
