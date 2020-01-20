CC=g++

all: task3
	./test

task3: test.o  
	$(CC) test.o -o test 

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o test