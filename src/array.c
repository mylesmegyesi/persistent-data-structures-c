#include <stdlib.h>
#include "array.h"

array_t* make_array(int size) {
  array_t* arr = malloc(sizeof(array_t));
  arr->arr = malloc(size * sizeof(void*));
  arr->size = size;
  return arr;
}

void array_set(array_t* arr, unsigned int index, void* value) {
  arr->arr[index] = value;
}

void* array_get(array_t* arr, unsigned int index) {
  return arr->arr[index];
}

void array_copy(array_t* source, unsigned int source_index, array_t* destination, unsigned int destination_index, unsigned int length) {
  unsigned int i, j;
  for (i = source_index, j=destination_index; i < source->size; i++, j++) {
    array_set(destination, j, array_get(source, i));
  }
}

void free_array(array_t* arr) {
  free(arr->arr);
  free(arr);
}
