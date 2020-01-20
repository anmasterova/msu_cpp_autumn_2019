CC=g++

all: task5
	./test

task5: test.o  
	$(CC) test.o -o test 

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o test