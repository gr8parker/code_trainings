
#include <stdlib.h> // for malloc
#include <stdio.h>
#include <assert.h> // for tests
#include "array.h"

const int kMinCapacity = 16;
const int kGrowthFactor = 2;

NArray *narray_new(int capacity) {
    int true_capacity = narray_determine_capacity(capacity);

    NArray *arr = (NArray*) malloc(sizeof(NArray));
    check_address(arr);

    arr->size = 0;
    arr->capacity = true_capacity;
    arr->data = (int*) malloc(sizeof(int)*true_capacity);
    check_address(arr->data);

    return arr;
}

void narray_delete(NArray **arr) {
    free((*arr)->data);
    free(*arr);
    *arr = NULL;
}

bool narray_isEmpty(NArray *arr) {
    assert(arr!= NULL);
    return !(arr->size);
}

int narray_size(NArray *arr) {
    assert(arr != NULL );
    return arr->size;
}

int narray_at(NArray *arr, int index) {
    assert(arr != NULL);
    return *(arr->data+index);
}

void narray_push_back(NArray *arr, int value) {
    narray_resize_for_size(arr, arr->size + 1);
    *(arr->data + arr->size ) = value;
    (arr->size)++;
}

int narray_pop_back(NArray *arr) {
    if(arr->size == 0 ) {
	perror("Error. Vector size is 0.\n");
	exit(EXIT_FAILURE);
    }
    narray_resize_for_size(arr, arr->size - 1);
    
    (arr->size)--;
    return *(arr->data + arr->size);
}

void narray_insert(NArray *arr, int index,int value) {
    assert(index >= 0);
    if ( (index > arr->size ) ) {
	perror("Error insert, index is out of range\n");
	exit(EXIT_FAILURE);
    } else {
	narray_resize_for_size(arr, arr->size + 1);
	int i = 0;
	int prev_val = value;
	for(i = index; i < arr->size+1; ++i) {
	    int tmp =  *(arr->data + i);
	    *(arr->data + i) = prev_val;
	    prev_val = tmp;	       
	}
	(arr->size)++;
    }
}

void narray_erase(NArray *arr, int index) {
    assert(index >= 0);
    if ( index > arr->size-1) {
    	perror("Error erase, index is out of range\n");
	exit(EXIT_FAILURE);
    } else {
	int i = index;
	for(i; i < arr->size-1; ++i) {
	    *(arr->data + i) = *(arr->data + i + 1);
	}
	narray_resize_for_size(arr, arr->size-1);
	(arr->size)--;
    }
}

int narray_pop_front(NArray *arr) {
    if( narray_isEmpty(arr) ) {
	perror("Error. Array is empty\n");
	exit(EXIT_FAILURE);
    }
    int value = *(arr->data);
    narray_erase(arr, 0);
    return value;
}

void narray_push_front(NArray *arr, int value) {
    narray_insert(arr, 0, value);
}

void narray_reverse(NArray *arr) {
    if (narray_isEmpty(arr)) return;
    else {
	int i = 0;
	int tmp = 0;
	for(i = 0; i < arr->size / 2; ++i){
	    tmp = *(arr->data + i);
	    *(arr->data+i) = *(arr->data + arr->size - 1 - i);
	    *(arr->data + arr->size - 1 - i) = tmp;
	}
    }
}

void narray_remove_value(NArray *arr, int value) {
    int i = 0;
    for( i = 0; i < arr->size; ++i) {
	if ( narray_at(arr, i) == value) {
	    narray_erase(arr, i);
	    break;
	}
    }
}
void narray_print(NArray *arr) {
    int i = 0;
    for(i; i < arr->size; ++i) {
	printf("%d ", narray_at(arr, i));
    }
    printf("\n");
}
    

void narray_resize_for_size(NArray *arr, int requested_size) {
    if( requested_size > arr->capacity ) { // growing up
	narray_grow_up_size(arr, requested_size);
    }
    else if ( requested_size < arr->capacity / kGrowthFactor ) {
	narray_shrink_down_size(arr, requested_size);	
    }
}

void narray_shrink_down_size(NArray *arr, int requested_size) {
    int new_capacity = arr->capacity / kGrowthFactor;
    if(new_capacity >= kMinCapacity ) {
	assert(arr->size <= new_capacity);		       
	int *new_data = (int*) malloc(new_capacity*sizeof(int));
	check_address(new_data);
	
	int i = 0;
	for(; i < arr->size; ++i) {
	    *(new_data+i) = *(arr->data+i);
	}
	free(arr->data);

	arr->data = new_data;
	arr->capacity = new_capacity;
    }
}


void narray_grow_up_size(NArray *arr, int requested_size) {
    int new_capacity = narray_determine_capacity(requested_size);
    int* new_data = (int*) malloc(new_capacity*sizeof(int));
    check_address(new_data);

    int i = 0;
    for(; i < arr->size; ++i) {
	*(new_data+i) = *(arr->data+i);
    }
    free(arr->data);

    arr->data = new_data;
    arr->capacity = new_capacity;
}
    
int narray_determine_capacity(int capacity)  {
    const int kMinInitialCapacity = 1;
    int true_capacity = kMinCapacity;

    if(capacity < kMinInitialCapacity) {
	perror("Unavailable size of vector\n");
	exit(EXIT_FAILURE);
    }
 
    while(capacity > true_capacity)
	true_capacity *= kGrowthFactor;
    
    return true_capacity;    
}

void check_address(void *addr) {
    if (addr == NULL){
	perror("Error. Unable to allocate memory. \n");
	exit(EXIT_FAILURE);
    }
}

bool testCapacity() {
    printf("Capacity testing ...\n");
    // init capacity
    NArray *arr = narray_new(kMinCapacity - 1);
    assert( (arr->capacity) == kMinCapacity);
    narray_delete(&arr);

    arr = narray_new(kMinCapacity+1);
    assert( (arr->capacity) == (kMinCapacity * kGrowthFactor) );
    narray_delete(&arr);
    return true;
}


bool testPushBack() {
    printf("Push_back test ... \n");
    NArray *arr = narray_new(1+kMinCapacity/2);
    int i = 0;
    for(i; i < kMinCapacity; ++i) {
	narray_push_back(arr,i);
    }
    for(i = 0; i < kMinCapacity; ++i) {
	assert(narray_at(arr,i) ==i);
    }
    assert( arr->capacity == kMinCapacity );
    assert( arr->size == kMinCapacity );

    narray_push_back(arr, kMinCapacity);
    assert( arr->capacity == kMinCapacity*2 );
    assert( arr->size == kMinCapacity+1 );
    narray_delete(&arr);
    return true;
}
    
    
bool testPopBack() {
    printf("Pop back test ...\n");
    NArray *arr = narray_new(1+kMinCapacity/2);
    int i = 0;
    for(i; i < kMinCapacity; ++i) {
	narray_push_back(arr, i);
    }
    narray_pop_back(arr);
    narray_push_back(arr, 20);
    assert(arr->capacity == kMinCapacity);
    assert( arr->size == kMinCapacity );

    narray_push_back(arr, 1);
    narray_push_back(arr, 2);
    assert(arr->capacity == kMinCapacity*2);

    narray_pop_back(arr);
    assert(arr->capacity == kMinCapacity*2);

    narray_pop_back(arr);
    narray_pop_back(arr);
    assert(arr->capacity == kMinCapacity);

    for(i = arr->size; i > 0; --i) {
	narray_pop_back(arr);
    }
    assert(arr->size == 0);
    assert(arr->capacity == kMinCapacity);

    narray_delete(&arr);    
    
    return true;
}

bool testInsert() {
    printf("Insert test ...\n");
    NArray *arr = narray_new(2);
    int i = 0;
    for(i = 0; i < kMinCapacity / 2; ++i) {
	narray_push_back(arr, i);
    }
    int idx = i;
    for(; i < kMinCapacity; ++i){
	narray_push_back(arr,i+1);
    }
    assert(arr->capacity == kMinCapacity);

    narray_insert(arr, idx, idx);
    assert(arr->capacity == kMinCapacity*2);

    for(i = 0; i < arr->size; ++i) {
	assert(narray_at(arr,i) == i);
    }
    narray_delete(&arr);
    return true;
}

bool testErase() {
    printf("Erase test ...\n");
    NArray *arr = narray_new(2);
    int i = 0;
    for(i = 0; i < kMinCapacity + 1; ++i) {
	narray_push_back(arr, i);
    }
    assert(arr->capacity == kMinCapacity*2);
    narray_erase(arr, 0);
    narray_erase(arr, 0);
    assert(arr->capacity == kMinCapacity);
    assert(narray_at(arr,0) == 2);
    assert(narray_at(arr,arr->size) == kMinCapacity);
    narray_delete(&arr);
    return true;
}

bool testPopFront() {
    printf("Pop/Push front test ...\n");
    NArray *arr = narray_new(2);
    
    narray_push_front(arr, 0);
    assert(arr->size == 1);
    assert( narray_pop_front(arr) == 0);

    narray_push_front(arr, 8);
    assert(arr->size == 1);
    assert( narray_pop_front(arr) == 8);
    
    assert(narray_isEmpty(arr) == 1);

    narray_delete(&arr);
    return true;
}

bool testReverse() {

    NArray *arr = narray_new(2);
    int i = 0;
    for(i = 0; i < kMinCapacity + 1; ++i) {
	narray_push_back(arr, i);
    }
    narray_print(arr);
    narray_reverse(arr);
    narray_print(arr);
    narray_remove_value(arr, 7);
    narray_print(arr);
    narray_delete(&arr);

    return true;
}
    

    
