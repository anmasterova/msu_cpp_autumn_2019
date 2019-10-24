CC=g++

all: task2
	./LinearAllocator

task2: LinearAllocator.o  
	$(CC) LinearAllocator.o -o LinearAllocator 

LinearAllocator.o: LinearAllocator.cpp
	$(CC) -c LinearAllocator.cpp

clean:
	rm -rf *.o LinearAllocator