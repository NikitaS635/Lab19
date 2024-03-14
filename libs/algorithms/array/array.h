#ifndef INC_ARRAY_H
#define INC_ARRAY_H

#include <stddef.h>

// Ввод массива data размера n
void inputArray_(int *a, size_t n);

// Вывод массива data размера n
void outputArray_(const int *a, size_t n);

// Возвращает значение первого вхождения элемента x
// в массиве a размера n при его наличии, иначе - n
size_t linearSearch_(const int *a, const size_t n, int x);

// Возвращает позицию вхождения элемента x
// в отсортированном массиве a размера n при его наличии, иначе - SIZE_MAX
size_t binarySearch_(const int *a, const size_t n, int x);

// Возвращает позицию первого элемента равного или большего x
// в отсортированном массиве a размера n
// при отсутствии такого элемента возвращает n
size_t binarySearchMoreOrEqual_(const int *a, const size_t n, int x);

// Вставка элемента со значением value
// в массив data размера n на позицию pos
void insert_(int *a, size_t *n, size_t pos, int value);

// Добавление элемента value в конец массива data размера n
void append_(int *a, size_t *n, int value);

// Удаление из массива data размера n элемента на позиции pos
// с сохранением порядка оставшихся элементов
void deleteByPosSaveOrder_(int *a, size_t *n, size_t pos);

// Удаление из массива data размера n элемента на позиции pos
// без сохранения порядка оставшихся элементов
// Размер массива data уменьшается на единицу
void deleteByPosUnsaveOrder_(int *a, size_t *n, size_t pos);

// Возвращает значение ’истина’ если все элементы
// массива data размера n соответствует функции-предикату predicate
// иначе - ’ложь’
int all_(const int *a, size_t n, int (*predicate)(int));

// Возвращает значение ’истина’ если хотя бы один элемент
// массива data размера n соответствует функции-предикату predicate
// иначе - ’ложь’
int any_(const int *a, size_t n, int (*predicate)(int));

// Применяет функцию predicate ко всем элементам массива source
// размера n и сохраняет результат в массиве dest размера n
void forEach_(const int *source, int *dest, size_t n, const int (*predicate)(int));

// Возвращает количество элементов массива data размера n
// удовлетворяющих функции-предикату predicate
int countIf_(const int *a, size_t n, int (*predicate)(int));

// Удаляет из массива data размера n все элементы, удовлетворяющие
// функции-предикату deletePredicate, записывает в n новый размер массива
void deleteIf_(int *a, size_t *n, int (*deletePredicate)(int));

#endif