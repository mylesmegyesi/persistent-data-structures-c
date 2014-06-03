CC = clang
CFLAGS = -Wall -std=c99
INCLUDE = -Iinclude
TEST_INCLUDE = -Itest
SOURCE := $(shell find src -name '*.c')
SOURCE_OBJECTS = $(SOURCE:.c=.o)
TESTS := $(shell find test -name '*_test.c')
TEST_OBJECTS = test/all_test_main.o $(TESTS:.c=.o) $(SOURCE_OBJECTS)
OUT = out
BIN = bin

src/%.o: src/%.c
	mkdir -p $(OUT)/$(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(OUT)/$@ $<

test/%.o: test/%.c
	mkdir -p $(OUT)/$(@D)
	$(CC) $(CFLAGS) $(TEST_INCLUDE) $(INCLUDE) -c -o $(OUT)/$@ $<

%_test_main.o: %_test_main.c
	mkdir -p $(OUT)/$(@D)
	$(CC) $(CFLAGS) $(TEST_INCLUDE) $(INCLUDE) -c -o $(OUT)/$@ $<

.PHONY: test
test: $(TEST_OBJECTS)
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(TEST_INCLUDE) $(INCLUDE) $(addprefix $(OUT)/, $(TEST_OBJECTS)) -o bin/test
	./$(BIN)/test
	valgrind --tool=memcheck --dsymutil=yes --leak-check=full ./$(BIN)/test

.PHONY: test_isolated
test_isolated: $(TEST_MAIN) $(TESTS) $(SOURCE_OBJECTS)
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(TEST_INCLUDE) $(INCLUDE) $(addprefix $(OUT)/, $(TEST_MAIN)) $(addprefix $(OUT)/, $(TESTS)) $(addprefix $(OUT)/, $(SOURCE_OBJECTS)) -o bin/test_isolated
	./$(BIN)/test_isolated
	valgrind --tool=memcheck --dsymutil=yes --leak-check=full ./$(BIN)/test_isolated

.PHONY: clean
clean:
	rm -rf bin out
