CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

FUNC_C = src/*.c
FUNC_O = src/*.o

OBJ = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))
OBJ_MAIN = $(patsubst %.c, %.o, $(wildcard main.c))

run : app.exe
	./app.exe

app.exe: $(OBJ) $(OBJ_MAIN)
	$(CC) -o $@ $^ -lm

clean:
	rm *.o *.exe $(FUNC_O)