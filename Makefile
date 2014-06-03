CC = clang

.PHONY: test
test: clean
	mkdir -p bin
	$(CC) test/main.c test/persistent_array_map_test.c src/persistent_array_map.c src/array.c src/map_key.c src/map_value.c -Itest -Iinclude -o bin/test
	./bin/test
	valgrind --tool=memcheck --dsymutil=yes --leak-check=full ./bin/test

.PHONY: clean
clean:
	rm -rf bin out

