#ifndef INC_BITSET_H
#define INC_BITSET_H

#include <stdint.h>
#include <stdbool.h>

typedef struct bitset {
    uint32_t *values;   // Указатель на массив значений (битовый массив)
    uint32_t maxValue;  // Максимальное значение элемента универсума
} bitset;

// Создание пустого множества с универсумом от 0 до maxValue
bitset bitset_create(unsigned maxValue);

// Проверка наличия значения в множестве
bool bitset_in(bitset set, unsigned int value);

// Проверка равенства двух множеств
bool bitset_isEqual(bitset set1, bitset set2);

// Проверка, является ли subset подмножеством set
bool bitset_isSubset(bitset subset, bitset set);

// Добавление элемента в множество
void bitset_insert(bitset *set, unsigned int value);

// Удаление элемента из множества
void bitset_deleteElement(bitset *set, unsigned int value);

// Объединение двух множеств
bitset bitset_union(bitset set1, bitset set2);

// Пересечение двух множеств
bitset bitset_intersection(bitset set1, bitset set2);

// Разность двух множеств
bitset bitset_difference(bitset set1, bitset set2);

// Симметричная разность двух множеств
bitset bitset_symmetricDifference(bitset set1, bitset set2);

// Дополнение множества до универсума
bitset bitset_complement(bitset set);

// Вывод множества
void bitset_print(bitset set);

#endif /* INC_BITSET_H */
