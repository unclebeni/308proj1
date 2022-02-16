CC = gcc 
CGLAGS = -I.
DEPS = message.h
OBJ = message.o lab1.o
%.o: $.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lab1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 
