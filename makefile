# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=g++
CPPFLAGS=-I. -std=c++11
DEPS = policies.hpp error_check.hpp dataStructures.hpp
OBJ = memsim.o dataStructures.o fifo.o lru.o vms.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

memsim: $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f *.o