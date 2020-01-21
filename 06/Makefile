CC=g++

all: task6
	./test

task6: test.o  
	$(CC) test.o -o test 

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o test