CC=g++

all: task1
	./calc $(file) "test.txt"

task1: calc.o  
	$(CC) calc.o -o calc 

calc.o: calc.cpp
	$(CC) -c calc.cpp

clean:
	rm -rf *.o calc