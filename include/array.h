#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct Array {
  unsigned int size;
  void** arr;
} array_t;

array_t* make_array(int size);
void array_set(array_t* arr, unsigned int index, void* value);
void* array_get(array_t* arr, unsigned int index);
void array_copy(array_t* source, unsigned int source_index, array_t* destination, unsigned int destination_index, unsigned int length);
void free_array(array_t* arr);

#endif
