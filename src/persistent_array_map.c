#include <stdlib.h>
#include <string.h>
#include "persistent_array_map.h"
#include "array.h"

persistent_array_map_t* make_persistent_array_map() {
  persistent_array_map_t* map = malloc(sizeof(persistent_array_map_t));
  map->arr = make_array(0);
  return map;
}

int map_index_of_key(persistent_array_map_t* map, map_key_t* key) {
  int i;
  array_t* arr = map->arr;
  for (i = 0; i < arr->size; i+=2) {
    map_key_t* index_key = (map_key_t*)array_get(arr, i);
    if (key->equals(key, index_key)) {
      return i;
    }
  }
  return -1;
}

persistent_array_map_t* map_assoc(persistent_array_map_t* map, map_key_t* key, map_value_t* value) {
  int key_index = map_index_of_key(map, key);
  if (key_index > -1) { // key exists
    map_value_t* existing_value = array_get(map->arr, key_index + 1);
    if (existing_value->equals(existing_value, value)) {
      return map; // key exists and value is the same, do nothing
    } else {
      persistent_array_map_t* new_map = malloc(sizeof(persistent_array_map_t));
      array_t* old_arr = map->arr;
      array_t* new_arr = make_array(old_arr->size);
      array_copy(old_arr, 0, new_arr, 0, old_arr->size);
      new_map->arr = new_arr;
      array_set(new_arr, key_index, (void*)key);
      array_set(new_arr, key_index + 1, (void*)value);
      return new_map;
    }
  } else {
    persistent_array_map_t* new_map = malloc(sizeof(persistent_array_map_t));
    array_t* old_arr = map->arr;
    array_t* new_arr = make_array(old_arr->size + 2);
    array_copy(old_arr, 0, new_arr, 2, old_arr->size);
    new_map->arr = new_arr;
    array_set(new_arr, 0, (void*)key);
    array_set(new_arr, 1, (void*)value);
    return new_map;
  }
}

map_value_t* map_get(persistent_array_map_t* map, map_key_t* key) {
  int key_index = map_index_of_key(map, key);
  if (key_index > -1) {
    return (map_value_t*)array_get(map->arr, key_index + 1);
  } else {
    return NULL;
  }
}

int map_count(persistent_array_map_t* map) {
  return map->arr->size / 2;
}

void free_persistent_array_map(persistent_array_map_t* map) {
  free_array(map->arr);
  free(map);
}
