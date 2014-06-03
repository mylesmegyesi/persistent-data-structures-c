#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "map_key.h"
#include "map_value.h"
#include "persistent_array_map.h"
#include "persistent_array_map_test.h"

int integer_value_equals(map_value_t* self, map_value_t* other) {
  return *(int*)self->obj == *(int*)other->obj;
}

map_value_t* make_integer_map_value(int* val) {
  map_value_t* value = malloc(sizeof(map_value_t));
  value->obj = val;
  value->equals = integer_value_equals;
  return value;
}

int string_key_equals(map_key_t* self, map_key_t* other) {
  return strcmp((char*)self->obj, (char*)other->obj) == 0;
}

map_key_t* make_string_map_key(char* str) {
  map_key_t* key = malloc(sizeof(map_key_t));
  key->obj = (void*)str;
  key->equals = string_key_equals;
  return key;
}

int* make_int(int i) {
  int* i_ptr = malloc(sizeof(int));
  *i_ptr = i;
  return i_ptr;
}

void creates_an_array_map() {
  persistent_array_map_t* map = make_persistent_array_map();

  assert(map_count(map) == 0);

  free_persistent_array_map(map);
}

void associates_a_key_to_a_value() {
  map_key_t* key = make_string_map_key("a key");
  int int_value = 50;
  map_value_t* value = make_integer_map_value(&int_value);
  persistent_array_map_t* map = make_persistent_array_map();
  persistent_array_map_t* map_two = map_assoc(map, key, value);

  map_value_t* found_value = map_get(map_two, key);
  assert(*(int*)found_value->obj == int_value);
  assert(map_count(map_two) == 1);

  free_map_key(key);
  free_map_value(value);
  free_persistent_array_map(map);
  free_persistent_array_map(map_two);
}

void does_not_mutate_the_map_on_assoc() {
  persistent_array_map_t* map = make_persistent_array_map();
  map_key_t* key = make_string_map_key("a key");
  int int_value = 50;
  map_value_t* value = make_integer_map_value(&int_value);
  persistent_array_map_t* map_two = map_assoc(map, key, value);

  map_value_t* found_value = map_get(map, key);
  assert(found_value == NULL);
  assert(map_count(map_two) == 1);

  free_map_key(key);
  free_map_value(value);
  free_persistent_array_map(map);
  free_persistent_array_map(map_two);
}

void associates_to_a_key_that_exists_but_the_value_is_not_the_same() {
  map_key_t* key = make_string_map_key("a key");
  map_key_t* different_key_same_value = make_string_map_key("a key");
  int int_value = 50;
  int second_int_value = 60;
  map_value_t* value = make_integer_map_value(&int_value);
  map_value_t* different_value = make_integer_map_value(&second_int_value);
  persistent_array_map_t* map = make_persistent_array_map();
  persistent_array_map_t* map_two = map_assoc(map, key, value);
  persistent_array_map_t* map_three = map_assoc(map_two, different_key_same_value, different_value);

  map_value_t* found_value = map_get(map_three, different_key_same_value);
  assert(*(int*)found_value->obj == second_int_value);
  assert(map_count(map_three) == 1);

  free_map_key(key);
  free_map_key(different_key_same_value);
  free_map_value(value);
  free_map_value(different_value);
  free_persistent_array_map(map);
  free_persistent_array_map(map_two);
  free_persistent_array_map(map_three);
}

void associates_to_a_key_that_exists_and_the_value_is_the_same() {
  map_key_t* key = make_string_map_key("a key");
  map_key_t* different_key_same_value = make_string_map_key("a key");
  int int_value = 50;
  int different_int_same_value = 50;
  map_value_t* value = make_integer_map_value(&int_value);
  map_value_t* different_value = make_integer_map_value(&different_int_same_value);

  persistent_array_map_t* map = make_persistent_array_map();
  persistent_array_map_t* map_two = map_assoc(map, key, value);
  persistent_array_map_t* map_three = map_assoc(map_two, different_key_same_value, different_value);

  assert(map_two == map_three);
  //assert(persistent_array_map_equals(map_two, map_three));
  //assert(map_two != map_three);

  free_map_key(key);
  free_map_key(different_key_same_value);
  free_map_value(value);
  free_map_value(different_value);
  free_persistent_array_map(map);
  free_persistent_array_map(map_two);
  //free_persistent_array_map(map_three);
}

void associates_multiple_items() {
  map_key_t* key_one = make_string_map_key("key one");
  map_key_t* key_two = make_string_map_key("key two");
  int int_value_one = 50;
  int int_value_two = 60;
  map_value_t* value_one = make_integer_map_value(&int_value_one);
  map_value_t* value_two = make_integer_map_value(&int_value_two);
  persistent_array_map_t* map = make_persistent_array_map();
  persistent_array_map_t* map_two = map_assoc(map, key_one, value_one);
  persistent_array_map_t* map_three = map_assoc(map_two, key_two, value_two);

  map_value_t* found_value_one = map_get(map_three, key_one);
  map_value_t* found_value_two = map_get(map_three, key_two);

  assert(*(int*)found_value_one->obj == int_value_one);
  assert(*(int*)found_value_two->obj == int_value_two);

  free_map_key(key_one);
  free_map_key(key_two);
  free_map_value(value_one);
  free_map_value(value_two);
  free_persistent_array_map(map);
  free_persistent_array_map(map_two);
  free_persistent_array_map(map_three);
}

void associates_multiple_items_then_to_a_key_that_exists() {
  map_key_t* key_one = make_string_map_key("key one");
  map_key_t* key_two = make_string_map_key("key two");
  map_key_t* different_key_one = make_string_map_key("key one");
  int int_value_one = 50;
  int int_value_two = 60;
  int int_value_three = 70;
  map_value_t* value_one = make_integer_map_value(&int_value_one);
  map_value_t* value_two = make_integer_map_value(&int_value_two);
  map_value_t* value_three = make_integer_map_value(&int_value_three);

  persistent_array_map_t* map = make_persistent_array_map();
  persistent_array_map_t* map_two = map_assoc(map, key_one, value_one);
  persistent_array_map_t* map_three = map_assoc(map_two, key_two, value_two);
  persistent_array_map_t* map_four = map_assoc(map_three, different_key_one, value_three);

  map_value_t* found_value_one = map_get(map_four, key_one);
  map_value_t* found_value_two = map_get(map_four, key_two);
  assert(map_count(map_four) == 2);
  assert(*(int*)found_value_one->obj == int_value_three);
  assert(*(int*)found_value_two->obj == int_value_two);

  free_map_key(key_one);
  free_map_key(key_two);
  free_map_key(different_key_one);
  free_map_value(value_one);
  free_map_value(value_two);
  free_map_value(value_three);
  free_persistent_array_map(map);
  free_persistent_array_map(map_two);
  free_persistent_array_map(map_three);
  free_persistent_array_map(map_four);
}

void associating_lots_of_data() {
  int iters = 1000;
  array_t* key_strings = make_array(iters);
  array_t* keys = make_array(iters);
  array_t* int_values = make_array(iters);
  array_t* values = make_array(iters);
  persistent_array_map_t* map = make_persistent_array_map();
  int i;
  for (i = 0; i < iters; i++) {
    char* key_string = (char*)malloc(sizeof(char) * 10);
    sprintf(key_string, "key%d", i);
    map_key_t* key = make_string_map_key(key_string);
    int* i_value = malloc(sizeof(int));
    *i_value = i;
    map_value_t* value = make_integer_map_value(i_value);
    persistent_array_map_t* new_map = map_assoc(map, key, value);

    assert(map_count(new_map) == (i + 1));
    map_value_t* found_value = map_get(new_map, key);
    assert(*(int*)found_value->obj == *i_value);

    free_persistent_array_map(map);
    map = new_map;
    array_set(keys, i, (void*)key);
    array_set(key_strings, i, (void*)key_string);
    array_set(values, i, (void*)value);
    array_set(int_values, i, (void*)i_value);
  }

  for(i = 0; i < iters; i++) {
    map_key_t* key = (map_key_t*)array_get(keys, i);
    char* key_string = (char*)array_get(key_strings, i);
    map_value_t* value = (map_value_t*)array_get(values, i);
    int* int_value = (int*)array_get(int_values, i);
    free_map_key(key);
    free(key_string);
    free_map_value(value);
    free(int_value);
  }

  free_array(keys);
  free_array(key_strings);
  free_array(values);
  free_array(int_values);

  free_persistent_array_map(map);
}

void persistent_array_map_tests() {
  creates_an_array_map();
  associates_a_key_to_a_value();
  does_not_mutate_the_map_on_assoc();
  associates_to_a_key_that_exists_but_the_value_is_not_the_same();
  associates_to_a_key_that_exists_and_the_value_is_the_same();
  associates_multiple_items();
  associates_multiple_items_then_to_a_key_that_exists();
  //associates_null_to_a_key();
  //associates_null_to_a_key_twice();
  associating_lots_of_data();
}
