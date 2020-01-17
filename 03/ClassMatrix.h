/*Matrix*/
#include <cstddef>

class Matrix
{
private:
	size_t rows, columns;	
	int* data;

public:
	class Row
	{

	private:
		size_t size;
		int* data;

	public:
		Row(int* data, size_t size);
		int& operator[](size_t column);

	};

	Matrix(size_t rows, size_t columns);
	~Matrix();

	int getRows() const;
	int getColumns() const;

	Row operator[](size_t row);
	const Matrix& operator*=(int factor);
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;
};