#include <cstring>
#include <stdexcept> 

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
		Row(int* data, size_t size) : 
			size(size), 
			data(data) {}

		int& operator[](size_t column) 
		{
			if (column >= size)
				throw std::out_of_range("Invalid input column");
			
			return data[column];
		}

		const int& operator[](const size_t column) const 
		{
			if (column >= size)
				throw std::out_of_range("Invalid input column");
			
			return data[column];
		}

	};

	Matrix(size_t rows, size_t columns) : 
		rows(rows), 
		columns(columns)
	{
		if ((rows < 0) || (columns < 0))
			throw std::out_of_range("Invalid input range");

		data = new int[rows*columns];
	}

	~Matrix()
	{
		delete[] data;
	}

	int getRows() const
	{
		return rows;
	}

	int getColumns() const
	{
		return columns;
	}

	Row operator[](size_t row)
	{
		if (row >= rows)
			throw std::out_of_range("Invalid input row");
		
		return Row(&data[row * columns], columns);
	}

	const Row operator[](const size_t row) const
	{
		if (row >= rows)
			throw std::out_of_range("Invalid input row");
		
		return Row(&data[row * columns], columns);
	}

	Matrix& operator*=(int factor)
	{
		for (size_t i = 0; i < rows*columns; i++) 
			data[i] *= factor;

		return *this;
	}

	bool operator==(const Matrix& other) const
	{
		if (rows != other.rows)
			return false;

		if (columns != other.columns)
			return false;

		for (size_t i = 0; i < rows*columns; i++)
			if (data[i] != other.data[i])
				return false;

		return true;
	}

	bool operator!=(const Matrix& other) const
	{
		return !(*this == other);
	}
};
