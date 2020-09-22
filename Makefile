C=g++
CFLAGS=-ldl -Wall -Wextra -pedantic
DEPS = Deque.h
OBJ = test.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Deque: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
