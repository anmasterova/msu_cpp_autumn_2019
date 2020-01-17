#include "ClassMatrix.h"

#include <cassert>
#include <iostream>

int main(){

	const size_t rows = 5;
	const size_t cols = 3;
	
	try
		{
			Matrix m(rows, cols);

			assert(m.getRows() == 5);
			assert(m.getColumns() == 3);

			m[1][2] = 5; // строка 1, колонка 2
			double x = m[1][2];

			assert(x == 5);

			m *= 3; // умножение на число

			assert(m[1][2] == 15);

			Matrix m1(rows, cols);

			if (m1 != m)
				std::cout << "Everything went well"  << std::endl;
		}
		catch(const std::out_of_range& err)
		{
			std::cout << "Out of Range error: " << err.what() << std::endl;
		}

	return 0;
}