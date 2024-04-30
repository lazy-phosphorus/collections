#include "array-list.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

int ArrayListConstruct(ArrayList* const restrict list,
                       const unsigned int initialCapacity,
                       const unsigned long elementSize,
                       CompareFunction* const compare) {
    if (list == NULL || initialCapacity == 0 || elementSize == 0 ||
        compare == NULL) {
        errno = EINVAL;
        return -1;
    }

    list->array = calloc(initialCapacity, elementSize);
    if (list->array == NULL) return -1;
    list->elementSize = elementSize;
    list->Capacity = initialCapacity;
    list->Size = 0;
    list->compare = compare;
    return 0;
}

ArrayList* ArrayListNew(const unsigned int initialCapacity,
                        const unsigned long elementSize,
                        CompareFunction* const compare) {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    if (list == NULL) return NULL;
    if (ArrayListConstruct(list, initialCapacity, elementSize, compare) == -1) {
        free(list);
        return NULL;
    }
    return list;
}

void ArrayListDestruct(ArrayList* const restrict list) {
    if (list == NULL) return;

    free(list->array);
    list->array = NULL;
    list->elementSize = 0;
    list->Capacity = 0;
    list->Size = 0;
}

void ArrayListDelete(ArrayList** const restrict list) {
    if (list == NULL || *list == NULL) return;

    ArrayListDestruct(*list);
    free(*list);
    *list = NULL;
}

void* ArrayListGet(const ArrayList* const restrict list,
                   const unsigned int index) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (index > list->Size) {
        errno = EDOM;
        return NULL;
    }

    return list->array + index * list->elementSize;
}

int ArrayListSet(ArrayList* const restrict list, const unsigned int index,
                 const void* const restrict value) {
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (index > list->Size) {
        errno = EDOM;
        return -1;
    }

    memcpy(list->array + index * list->elementSize, value, list->elementSize);
    return 0;
}

void* ArrayListBack(const ArrayList* const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->array + list->elementSize * (list->Size - 1);
}

void* ArrayListFront(const ArrayList* const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->array;
}

int ArrayListPushBack(ArrayList* const restrict list,
                      const void* const restrict value) {
    void* temp = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (list->Size == list->Capacity) {
        list->Capacity *= 2;
        temp = calloc(list->Capacity, list->elementSize);
        if (temp == NULL) return -1;
        memcpy(temp, list->array, list->Size * list->elementSize);
        free(list->array);
        list->array = temp;
    }
    memcpy(list->array + list->Size * list->elementSize, value,
           list->elementSize);
    list->Size++;
    return 0;
}

void ArrayListPopBack(ArrayList* const restrict list) {
    if (list == NULL || list->Size == 0) return;
    list->Size--;
}

int ArrayListPushFront(ArrayList* const restrict list,
                       const void* const restrict value) {
    void* temp = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (list->Size == list->Capacity) {
        list->Capacity *= 2;
        temp = calloc(list->Capacity, list->elementSize);
        if (temp == NULL) return -1;
        memcpy(temp + list->elementSize, list->array,
               list->Size * list->elementSize);
        free(list->array);
        list->array = temp;
    } else {
        memmove(list->array + list->elementSize, list->array,
                list->Size * list->elementSize);
    }
    memcpy(list->array, value, list->elementSize);
    list->Size++;
    return 0;
}

void ArrayListPopFront(ArrayList* const restrict list) {
    if (list == NULL || list->Size == 0) return;
    list->Size--;
    memmove(list->array, list->array + list->elementSize,
            list->elementSize * list->Size);
}

int ArrayListInsert(ArrayList* const restrict list, const unsigned int index,
                    const void* const restrict value) {
    void* temp = NULL;
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (list->Size == list->Capacity) {
        if (list->Size == list->Capacity) {
            list->Capacity *= 2;
            temp = calloc(list->Capacity, list->elementSize);
            if (temp == NULL) return -1;
            memcpy(temp, list->array, index * list->elementSize);
            memcpy(temp + list->elementSize * (index + 1),
                   list->array + list->elementSize * index,
                   list->elementSize * (list->Size - index));
            free(list->array);
            list->array = temp;
        }
    } else {
        memmove(list->array + list->elementSize * (index + 1),
                list->array + list->elementSize * index,
                list->elementSize * (list->Size - index));
    }
    memcpy(list->array + list->elementSize * index, value, list->elementSize);
    list->Size++;
    return 0;
}

int ArrayListFind(const ArrayList* const restrict list,
                  const void* const restrict value) {
    if (list == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        if (list->compare(list->array + list->elementSize * i, value) == 0)
            return i;
    }
    return -1;
}

ArrayList* ArrayListSlice(const ArrayList* const restrict list,
                          const unsigned int start, const unsigned int size) {
    ArrayList* slice = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (start + size > list->Size) {
        errno = EDOM;
        return NULL;
    }
    slice = ArrayListNew(size, list->elementSize, list->compare);
    if (slice == NULL) return NULL;
    memcpy(slice->array, list->array + list->elementSize * start,
           list->elementSize * size);
    return slice;
}

static inline void swap(void* const restrict a, void* const restrict b,
                        void* const restrict cache,
                        const unsigned long elementSize) {
    memcpy(cache, a, elementSize);
    memcpy(a, b, elementSize);
    memcpy(b, cache, elementSize);
}

static int quickSort(ArrayList* const restrict list, const unsigned int left,
                     const unsigned int right, void* cache) {
    unsigned int pivot = (left + right) / 2, i = left, j = right;
    while (i < j) {
        while (i < pivot &&
               list->compare(list->array + i * list->elementSize,
                             list->array + pivot * list->elementSize) <= 0) {
            i++;
        }
        swap(list->array + i * list->elementSize,
             list->array + pivot * list->elementSize, cache, list->elementSize);
        pivot = i;
        while (pivot < j &&
               list->compare(list->array + j * list->elementSize,
                             list->array + pivot * list->elementSize) > 0) {
            j--;
        }
        swap(list->array + j * list->elementSize,
             list->array + pivot * list->elementSize, cache, list->elementSize);
        pivot = j;
        printf("i = %d, j = %d, pivot = %d\n", i, j, pivot);
    }

    if (pivot != left && quickSort(list, left, pivot - 1, cache) == -1)
        return -1;
    if (pivot != right && quickSort(list, pivot + 1, right, cache) == -1)
        return -1;
    return 0;
}

int ArrayListQuickSort(ArrayList* const restrict list) {
    void* cache = NULL;
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    cache = malloc(list->elementSize);
    if (cache == NULL) return -1;
    return quickSort(list, 0, list->Size - 1, cache);
}
