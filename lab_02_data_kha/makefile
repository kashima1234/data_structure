CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic

inc = ./inc/
obj = ./obj/
src = ./src/

app.exe: $(obj)main.o $(obj)io.o $(obj)sorts.o $(obj)file_parsing.o
	$(CC) -o $@ $^

$(obj)main.o: main.c $(inc)io.h $(inc)sorts.h $(inc)file_parsing.h $(inc)data_struct.h
	$(CC) -I$(inc) $(CFLAGS) -c $< -o $@

$(obj)io.o: $(src)io.c $(inc)io.h
	$(CC) -I$(inc) $(CFLAGS) -c $< -o $@

$(obj)sorts.o: $(src)sorts.c $(inc)sorts.h
	$(CC) -I$(inc) $(CFLAGS) -c $< -o $@

$(obj)file_parsing.o: $(src)file_parsing.c $(inc)file_parsing.h $(inc)io.h
	$(CC) -I$(inc) $(CFLAGS) -c $< -o $@

del:clean
.PHONY: clean
clean:
	rm -rf $(obj)*.o *.exe
	
	
	
 
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


