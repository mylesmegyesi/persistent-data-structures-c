#ifndef MAP_KEY_H_
#define MAP_KEY_H_

typedef struct MapKey {
  unsigned int (* hash_code)();
  int (* equals)(struct MapKey* self, struct MapKey* other);
  void* obj;
} map_key_t;

void free_map_key(map_key_t* key);

#endif
