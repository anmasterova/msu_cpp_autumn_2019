CC=g++

all: task3
	./ClassMatrix

task3: ClassMatrix.o  
	$(CC) ClassMatrix.o main.cpp -o ClassMatrix 

ClassMatrix.o: ClassMatrix.cpp
	$(CC) -c ClassMatrix.cpp

clean:
	rm -rf *.o ClassMatrix