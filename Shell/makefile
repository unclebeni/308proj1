CC = gcc 
CGLAGS = -I.
DEPS = myshell.c
OBJ = myshell.o
%.o: $.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myshell : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 
