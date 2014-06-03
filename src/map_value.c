#include <stdlib.h>
#include "map_value.h"

void free_map_value(map_value_t* value) {
  free(value);
}
