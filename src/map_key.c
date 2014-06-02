#include <stdlib.h>
#include "map_key.h"

void free_map_key(map_key_t* key) {
  free(key);
}
