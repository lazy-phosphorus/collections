**<h1 align="center">Collections</h1>**

A generic collection library without macro definitions for C.

## **Foreword**

Because C is not object-oriented programming language, all the generic collections in this repository are implemented by `void *`. Moreover, this library is mainly used by my self, and is **NOT** well tested. Please think twice before using this library.

## **Build**

This library is only tested on Linux. Windows/MacOS is able to compile in theory.

### **Prequisite**

- gcc(**NOT** tested) or clang(tested on 16.0.6).
- cmake(tested on 3.28.3).

### **Compile**

Clone this repository.

```sh
git clone https://github.com/lazy-phosphorus/collections.git
cd collections
```

Build release libraries.

```sh
mkdir build
cd build
cmake  -DCMAKE_BUILD_TYPE=Release ..  && make
```

(Optional) Build debug libraries.

```sh
cmake -DCMAKE_BUILD_TYPE=Debug .. && make
ctest # Run all the unit test.
```

## **Usage**

All the usages are written in comments of headers.
