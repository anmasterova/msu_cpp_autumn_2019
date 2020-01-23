CC=g++

all: task8
	./test

task8: test.o  
	$(CC) -pthread test.o -o test 

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o test