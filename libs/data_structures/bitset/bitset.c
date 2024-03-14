#include "bitset.h"
#include <stdlib.h>
#include <stdio.h>

bitset bitset_create(unsigned maxValue) {
    bitset set;
    set.maxValue = maxValue;
    set.values = (uint32_t *)calloc((maxValue / 32) + 1, sizeof(uint32_t));
    return set;
}

bool bitset_in(bitset set, unsigned int value) {
    if (value > set.maxValue) {
        fprintf(stderr, "Значение вне диапазона\n");
        exit(EXIT_FAILURE);
    }
    int index = value / 32;
    int pos = value % 32;
    return set.values[index] & (1 << pos);
}

bool bitset_isEqual(bitset set1, bitset set2) {
    if (set1.maxValue != set2.maxValue) {
        return false;
    }
    for (int i = 0; i <= set1.maxValue / 32; ++i) {
        if (set1.values[i] != set2.values[i]) {
            return false;
        }
    }
    return true;
}

bool bitset_isSubset(bitset subset, bitset set) {
    for (int i = 0; i <= subset.maxValue / 32; ++i) {
        if ((subset.values[i] & set.values[i]) != subset.values[i]) {
            return false;
        }
    }
    return true;
}

void bitset_insert(bitset *set, unsigned int value) {
    if (value > set->maxValue) {
        fprintf(stderr, "Значение вне диапазона\n");
        exit(EXIT_FAILURE);
    }
    int index = value / 32;
    int pos = value % 32;
    set->values[index] |= (1 << pos);
}

void bitset_deleteElement(bitset *set, unsigned int value) {
    if (value > set->maxValue) {
        fprintf(stderr, "Значение вне диапазона\n");
        exit(EXIT_FAILURE);
    }
    int index = value / 32;
    int pos = value % 32;
    set->values[index] &= ~(1 << pos);
}

bitset bitset_union(bitset set1, bitset set2) {
    bitset result = bitset_create(set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue);
    for (int i = 0; i <= result.maxValue / 32; ++i) {
        result.values[i] = set1.values[i] | set2.values[i];
    }
    return result;
}

bitset bitset_intersection(bitset set1, bitset set2) {
    bitset result = bitset_create(set1.maxValue < set2.maxValue ? set1.maxValue : set2.maxValue);
    for (int i = 0; i <= result.maxValue / 32; ++i) {
        result.values[i] = set1.values[i] & set2.values[i];
    }
    return result;
}

bitset bitset_difference(bitset set1, bitset set2) {
    bitset result = bitset_create(set1.maxValue);
    for (int i = 0; i <= set1.maxValue / 32; ++i) {
        result.values[i] = set1.values[i] & ~(set2.values[i]);
    }
    return result;
}

bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    bitset result = bitset_create(set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue);
    for (int i = 0; i <= result.maxValue / 32; ++i) {
        result.values[i] = set1.values[i] ^ set2.values[i];
    }
    return result;
}

bitset bitset_complement(bitset set) {
    bitset result = bitset_create(set.maxValue);
    for (int i = 0; i <= set.maxValue / 32; ++i) {
        result.values[i] = ~set.values[i];
    }
    return result;
}

void bitset_print(bitset set) {
    printf("{ ");
    for (unsigned int i = 0; i <= set.maxValue; ++i) {
        if (bitset_in(set, i)) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}
