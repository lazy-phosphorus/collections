#ifndef __TEST__
#define __TEST__

typedef struct {
    int a;
    int b;
    int c;
} Test;

int compare(const void *const a, const void *const b) {
    const Test *former = (const Test *)a, *latter = (const Test *)b;
    return former->a - latter->a;
}

#endif  // __TEST__
