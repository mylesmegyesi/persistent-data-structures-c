#include <stdlib.h>
#include <string.h>
#include "array.h"

#include <stdio.h>

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
  void* source_start = &source->arr[source_index];
  void* destination_start = &destination->arr[destination_index];
  unsigned int num = length * sizeof(void*);
  memcpy(destination_start, source_start, num);
}

void free_array(array_t* arr) {
  free(arr->arr);
  free(arr);
}
