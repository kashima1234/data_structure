.PHONY : clean

run : app.exe
	./app.exe

app.exe : main.c src/*.c
	gcc -std=c99 -Wall -pedantic -o app.exe *.c src/*.c
	
clean :
	rm -rf *.o *.exe