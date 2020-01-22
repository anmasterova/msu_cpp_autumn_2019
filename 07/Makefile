CC=g++

all: task7
	./test

task7: test.o  
	$(CC) test.o -o test 

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -rf *.o test