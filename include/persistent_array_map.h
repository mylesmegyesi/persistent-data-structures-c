#ifndef PERSISTENT_ARRAY_MAP_H_
#define PERSISTENT_ARRAY_MAP_H_

typedef struct Array {
  unsigned int size;
  void** arr;
} array_t;

typedef struct MapKey {
  unsigned int (* hash_code)();
  int (* equals)(struct MapKey* self, struct MapKey* other);
  void* obj;
} map_key_t;

typedef struct MapValue {
  void* obj;
  int (* equals)(struct MapValue* self, struct MapValue* other);
} map_value_t;

typedef struct PersistentArrayMap {
  array_t* arr;
} persistent_array_map_t;

array_t* make_array(int size);
void array_set(array_t* arr, unsigned int index, void* value);
void* array_get(array_t* arr, unsigned int index);
void array_copy(array_t* source, unsigned int source_index, array_t* destination, unsigned int destination_index, unsigned int length);
persistent_array_map_t* make_persistent_array_map();
persistent_array_map_t* map_assoc(persistent_array_map_t* map, map_key_t* key, map_value_t* value);
map_value_t* map_get(persistent_array_map_t* map, map_key_t* key);
int map_count(persistent_array_map_t* map);

#endif
