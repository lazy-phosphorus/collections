#include "array-list.h"

#include <errno.h>
#include <malloc.h>
#include <memory.h>

int ArrayListConstruct(ArrayList* const restrict list,
                       const unsigned int initialCapacity,
                       const unsigned long elementSize,
                       CompareFunction* const compare) {
    if (list == NULL || initialCapacity == 0 || elementSize == 0 ||
        compare == NULL) {
        errno = EINVAL;
        return -1;
    }

    list->list = calloc(initialCapacity, elementSize);
    if (list->list == NULL) return -1;
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

    free(list->list);
    list->list = NULL;
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

    return list->list + index * list->elementSize;
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

    memcpy(list->list + index * list->elementSize, value, list->elementSize);
    return 0;
}

void* ArrayListBack(const ArrayList* const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->list + list->elementSize * (list->Size - 1);
}

void* ArrayListFront(const ArrayList* const restrict list) {
    if (list == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if (list->Size == 0) return NULL;
    return list->list;
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
        memcpy(temp, list->list, list->Size * list->elementSize);
        free(list->list);
        list->list = temp;
    }
    memcpy(list->list + list->Size * list->elementSize, value,
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
        memcpy(temp + list->elementSize, list->list,
               list->Size * list->elementSize);
        free(list->list);
        list->list = temp;
    } else {
        memmove(list->list + list->elementSize, list->list,
                list->Size * list->elementSize);
    }
    memcpy(list->list, value, list->elementSize);
    list->Size++;
    return 0;
}

void ArrayListPopFront(ArrayList* const restrict list) {
    if (list == NULL || list->Size == 0) return;
    list->Size--;
    memmove(list->list, list->list + list->elementSize,
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
            memcpy(temp, list->list, index * list->elementSize);
            memcpy(temp + list->elementSize * (index + 1),
                   list->list + list->elementSize * index,
                   list->elementSize * (list->Size - index));
            free(list->list);
            list->list = temp;
        }
    } else {
        memmove(list->list + list->elementSize * (index + 1),
                list->list + list->elementSize * index,
                list->elementSize * (list->Size - index));
    }
    memcpy(list->list + list->elementSize * index, value, list->elementSize);
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
        if (list->compare(list->list + list->elementSize * i, value) == 0)
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
    memcpy(slice->list, list->list + list->elementSize * start,
           list->elementSize * size);
    return slice;
}
