#ifndef __TEST__
#define __TEST__

typedef struct {
    int a;
    int b;
    int c;
} Test;

int compare(const void *const a, const void *const b) {
    const Test *former = (const Test *)a, *latter = (const Test *)b;
    return former->a == latter->a && former->b == latter->b &&
                   former->c == latter->c
               ? 0
               : 1;
}

#endif  // __TEST__
