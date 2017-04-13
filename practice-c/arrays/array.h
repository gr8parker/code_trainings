
#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H

#include <assert.h>
#include <stdbool.h>

const int kMinCapacity;
const int kGrowthFactor;

typedef struct NMImplementationArray {
    int size;
    int capacity;
    int* data;
} NArray;

// initialize an array
NArray *narray_new(int capacity);
// destroy array
void narray_delete(NArray **arr);
// return number of elements in vector
int narray_size(NArray *arr);
void narray_push_back(NArray *arr, int value);
bool narray_isEmpty(NArray *arr);
int narray_at(NArray *arr, int index);
void narray_insert(NArray *arr, int index, int value);
void narray_push_front(NArray *arr, int value);
void narray_erace(NArray *arr, int index);
int narray_pop_front(NArray *arr);
void narray_print(NArray *arr);
void narray_reverse(NArray *arr);
void narray_remove_value(NArray *arr, int value);

/*--------------UTILITS--------------------*/
// deteremine capacity as a power of 2: 16, 32, 64
int narray_determine_capacity(int capacity);
void narray_resize_for_size(NArray *arr, int requested_size);
void narray_grow_up_size(NArray *arr, int requested_size) ;

void narray_shrink_down_size(NArray *arr, int requested_size);


// check if the memory was allocated
void check_address(void *addr);

/*--------------TESTS------------------------*/
bool testCapacity();

bool testPushBack();
bool testPopBack();
bool testInsert();
bool testErase();
bool testPopFront();
bool testReverse();
#endif // PROJECT_ARRAY_H
