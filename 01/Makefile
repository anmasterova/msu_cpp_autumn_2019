CC=g++

all: task1
	./test $(file) "test.txt"

task1: test.o  
	$(CC) test.o -o test 

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o test
