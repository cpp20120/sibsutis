CC = gcc -Wall -Wextra -Werror -std=c11 -g
TARGET = libterm.a
COMPILE_C = $(CC) -c $< -o $@

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, obj/%.o, $(SRC))

TEST_SRC = $(wildcard test/*.c)
TEST_OBJ = $(patsubst test/%.c, obj/%.o, $(TEST_SRC))
TEST_LIBS = -lcheck -lrt -lpthread -lsubunit -lm
TEST_TARGET = test.out

all: dirs build build-test

reall : clean dirs build build-test

$(TARGET): $(OBJ)
	ar rc $@ $^

build: $(TARGET)

clean:
	rm -rf obj test.out libterm.a

rebuild: clean build

$(TEST_TARGET): $(OBJ) $(TEST_OBJ) $(TEST_LIBS)
	$(CC) -o $@ $^

build-test: $(TEST_TARGET)

run-test:
	./test.out

test: build-test run-test

obj/%.o : %.c
	$(COMPILE_C)

obj/%.o : test/%.c
	$(COMPILE_C)

dirs:
	@mkdir -p obj

.PHONY: all reall build clean rebuild build-test run-test test dirs
