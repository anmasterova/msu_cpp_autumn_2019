CC=g++

all: task9
	./test

task9: test.o  
	$(CC) -pthread test.o -o test 

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o test