#include "array.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

int ArrayConstruct(Array* const restrict array,
                   const unsigned int initialCapacity,
                   const unsigned long elementSize) {
    if (array == NULL || initialCapacity == 0 || elementSize == 0) {
        errno = EINVAL;
        return -1;
    }

    array->array = calloc(initialCapacity, elementSize);
    if (array->array == NULL) return -1;
    array->elementSize = elementSize;
    array->Capacity = initialCapacity;
    array->Size = 0;
    return 0;
}

Array* ArrayNew(const unsigned int initialCapacity,
                const unsigned long unitSize) {
    Array* array = (Array*)malloc(sizeof(Array));
    if (array == NULL) return NULL;
    if (ArrayConstruct(array, initialCapacity, unitSize) == -1) {
        free(array);
        return NULL;
    }
    return array;
}

void ArrayDestruct(Array* const restrict array) {
    if (array == NULL) return;

    free(array->array);
    array->array = NULL;
    array->elementSize = 0;
    array->Capacity = 0;
    array->Size = 0;
}

void ArrayDelete(Array** const restrict array) {
    if (array == NULL) return;

    ArrayDestruct(*array);
    free(*array);
    *array = NULL;
}

void* ArrayGet(const Array* const restrict array, const unsigned int index) {
    if (array == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (index > array->Size) {
        errno = EDOM;
        return NULL;
    }

    return array->array + index * array->elementSize;
}

int ArraySet(Array* const restrict array, const unsigned int index,
             const void* const restrict value) {
    if (array == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (index > array->Size) {
        errno = EDOM;
        return -1;
    }

    memcpy(array->array + index * array->elementSize, value,
           array->elementSize);
    return 0;
}

int ArrayPushBack(Array* const restrict array,
                  const void* const restrict value) {
    void* temp = NULL;
    if (array == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (array->Size == array->Capacity) {
        array->Capacity *= 2;
        temp = calloc(array->Capacity, array->elementSize);
        if (temp == NULL) return -1;
        memcpy(temp, array->array, array->Size * array->elementSize);
        free(array->array);
        array->array = temp;
    }
    memcpy(array->array + array->Size * array->elementSize, value,
           array->elementSize);
    array->Size++;
    return 0;
}

int ArrayPushFront(Array* const restrict array,
                   const void* const restrict value) {
    void* temp = NULL;
    if (array == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (array->Size == array->Capacity) {
        array->Capacity *= 2;
        temp = calloc(array->Capacity, array->elementSize);
        memcpy(temp + array->elementSize, array->array,
               array->Size * array->elementSize);
        free(array->array);
        array->array = temp;
    } else {
        memmove(array->array + array->elementSize, array->array,
                array->Size * array->elementSize);
    }
    memcpy(array->array, value, array->elementSize);
    array->Size++;
    return 0;
}

int ArrayInsert(Array* const restrict array, const unsigned int index,
                const void* const restrict value) {
    void* temp = NULL;
    if (array == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (array->Size == array->Capacity) {
        if (array->Size == array->Capacity) {
            array->Capacity *= 2;
            temp = calloc(array->Capacity, array->elementSize);
            memcpy(temp, array->array, index * array->elementSize);
            memcpy(temp + array->elementSize * (index + 1),
                   array->array + array->elementSize * index,
                   array->elementSize * (array->Size - index));
            free(array->array);
            array->array = temp;
        }
    } else {
        memmove(array->array + array->elementSize * (index + 1),
                array->array + array->elementSize * index,
                array->elementSize * (array->Size - index));
    }
    memcpy(array->array + array->elementSize * index, value,
           array->elementSize);
    array->Size++;
    return 0;
}
