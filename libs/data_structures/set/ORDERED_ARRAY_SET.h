#ifndef INC_ORDERED_ARRAY_SET_H
#define INC_ORDERED_ARRAY_SET_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



typedef struct ordered_array_set {
    int *data; // элементы множества
    size_t size; // количество элементов в множестве
    size_t capacity; // максимальное количество элементов в множестве
} ordered_array_set;

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create(size_t capacity);

ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size);

size_t ordered_array_set_in(ordered_array_set *set, int value);

bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2);

bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set);

void ordered_array_set_isAbleAppend(ordered_array_set *set);

void ordered_array_set_insert(ordered_array_set *set, int value);

void ordered_array_set_deleteElement(ordered_array_set *set, int value);

ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2);

ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2);

ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2);

ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2);

ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet);

void ordered_array_set_print(ordered_array_set set);

void ordered_array_set_delete(ordered_array_set *set);

#endif
