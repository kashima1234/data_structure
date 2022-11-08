.PHONY : clear

cc := gcc
c_flags := -Wall -Werror -pedantic -std=c99

func_src := ./src/*.c
func_obj := ./src/*.o

objs := $(patsubst %.c, %.o, $(wildcard $(func_src)))
main_obj := $(patsubst %.c, %.o, $(wildcard main.c))

run : app.exe
	./app.exe

app.exe : $(main_obj) $(objs) 
	$(cc) $(c_flags) -o $@ $^ -lm

clear :
	rm -rf ./src/*.o *./o *.exe *.out