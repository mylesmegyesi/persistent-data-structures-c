#ifndef PERSISTENT_ARRAY_MAP_H_
#define PERSISTENT_ARRAY_MAP_H_

#include "map_key.h"
#include "map_value.h"
#include "array.h"

typedef struct PersistentArrayMap {
  array_t* arr;
} persistent_array_map_t;

persistent_array_map_t* make_persistent_array_map();
persistent_array_map_t* map_assoc(persistent_array_map_t* map, map_key_t* key, map_value_t* value);
map_value_t* map_get(persistent_array_map_t* map, map_key_t* key);
int map_count(persistent_array_map_t* map);
void free_persistent_array_map(persistent_array_map_t* map);

#endif
