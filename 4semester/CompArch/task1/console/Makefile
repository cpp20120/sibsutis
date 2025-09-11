CC = gcc -Wall -Wextra -Werror -std=c11 -g

TARGET = console.out
LIBS = -L../mySimpleComputer -L../myTerm -L../myBigChars -L../myReadkey -lsimplecomputer -lterm -lmybigchars -lreadkey
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, obj/%.o, $(SRC))

all : dirs build

clean :
	rm -rf obj *.out *.bin

rebuild : clean all

$(TARGET) : $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

build : $(TARGET)

test :

dirs :
	@mkdir -p obj

obj/%.o : %.c
	$(CC) -c $< -o $@

.PHONY : all build clean test dirs $(TARGET) rebuild
