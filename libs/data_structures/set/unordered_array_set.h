#ifndef INC_UNORDERED_ARRAY_SET_H
#define INC_UNORDERED_ARRAY_SET_H

#include <stdint.h>
#include <stdbool.h>

typedef struct unordered_array_set {
    int *data;      // элементы множества
    size_t size;    // количество элементов в множестве
    size_t capacity;    // максимальное количество элементов в множестве
} unordered_array_set;

unordered_array_set unordered_array_set_create(size_t capacity);

unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size);

size_t unordered_array_set_in(unordered_array_set set, int value);

size_t unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set);

bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2);

void unordered_array_set_isAbleAppend(unordered_array_set *set);

bool unordered_array_set_insert(unordered_array_set *set, int value);

void unordered_array_set_deleteElement(unordered_array_set *set, int value);

unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2);

unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2);

unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2);

unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet);

unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2);

void unordered_array_set_print(unordered_array_set set);

void unordered_array_set_delete(unordered_array_set set);

#endif
