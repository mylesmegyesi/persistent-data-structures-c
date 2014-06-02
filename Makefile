CC = clang

.PHONY: test
test: clean
	mkdir -p bin
	$(CC) test/main.c test/persistent_array_map_test.c src/persistent_array_map.c -Itest -Iinclude -o bin/test
	./bin/test

.PHONY: clean
clean:
	rm -rf bin out
