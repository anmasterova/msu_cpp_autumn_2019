all: task0; 

task0: task0_by_rows task0_by_columns 
	./task0_by_rows.exe && ./task0_by_columns.exe

task0_by_rows: 
	g++ task0_by_rows.cpp -o task0_by_rows.exe

task0_by_columns: 
	g++ task0_by_columns.cpp -o task0_by_columns.exe

clean: 
	del /f *.exe           
