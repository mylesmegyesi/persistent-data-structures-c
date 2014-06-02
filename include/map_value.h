#ifndef MAP_VALUE_H_
#define MAP_VALUE_H_

typedef struct MapValue {
  void* obj;
  int (* equals)(struct MapValue* self, struct MapValue* other);
} map_value_t;

#endif
