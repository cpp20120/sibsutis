CC = gcc -Wall -Wextra -Werror -std=c11 -g
TARGET = libmybigchars.a
COMPILE_C = $(CC) -c $< -o $@
LIBS = -L../myTerm -lterm

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
	rm -rf obj $(TEST_TARGET) $(TARGET)

rebuild: clean build

$(TEST_TARGET): $(OBJ) $(TEST_OBJ) $(TEST_LIBS)
	$(CC) -o $@ $^ $(LIBS)

build-test: $(TEST_TARGET)

run-test:
	./$(TEST_TARGET)

test: build-test run-test

obj/%.o : %.c
	$(COMPILE_C)

obj/%.o : test/%.c
	$(COMPILE_C)

dirs:
	@mkdir -p obj

.PHONY: all reall build clean rebuild build-test run-test test dirs
