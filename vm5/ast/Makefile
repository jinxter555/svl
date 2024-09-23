SHELL := /bin/bash
CC=g++ -std=c++17 -g
# Define temporary directory
TMPDIR = /dev/shm

objects = entity.o

all: $(objects)
#	$(CC)  $^ -o all

$(objects): %.o: %.cc
	$(CC) -c $^ -o $@

clean:
	rm -f out *.o *.gch *.out
