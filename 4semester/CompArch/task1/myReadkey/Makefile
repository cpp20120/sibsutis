CC = gcc -Wall -Wextra -Werror -std=c11 -g
TARGET = libreadkey.a
COMPILE_C = $(CC) -c $< -o $@

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, obj/%.o, $(SRC))

all: dirs build

reall : clean dirs build

$(TARGET): $(OBJ)
	ar rc $@ $^

build: $(TARGET)

clean:
	rm -rf obj $(TARGET)

rebuild: clean build

obj/%.o : %.c
	$(COMPILE_C)

dirs:
	@mkdir -p obj

.PHONY: all reall build clean rebuild dirs
