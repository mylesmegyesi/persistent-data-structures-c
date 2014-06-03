#ifndef MAP_VALUE_H_
#define MAP_VALUE_H_

typedef struct MapValue {
  void* obj;
  int (* equals)(struct MapValue* self, struct MapValue* other);
} map_value_t;

void free_map_value(map_value_t* value);

#endif
