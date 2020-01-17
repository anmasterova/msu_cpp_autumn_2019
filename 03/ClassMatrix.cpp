/*Matrix*/

#include "ClassMatrix.h"

#include <stdexcept>

Matrix::Row::Row(int* data, size_t size) : 
	size(size), 
	data(data) {}

int& Matrix::Row::operator[](size_t column) 
{
	if (column >= size)
		throw std::out_of_range("Invalid input column");
	
	return data[column];
}

Matrix::Matrix(size_t rows, size_t columns) : 
	rows(rows), 
	columns(columns)
{
	if ((rows < 0) || (columns < 0))
		throw std::out_of_range("Invalid input range");

	data = new int[rows*columns];
}

Matrix::~Matrix()
{
	delete[] data;
}

int Matrix::getRows() const
{
	return rows;
}

int Matrix::getColumns() const
{
	return columns;
}

Matrix::Row Matrix::operator[](size_t row)
{
	if (row >= rows)
		throw std::out_of_range("Invalid input row");
	
	return Row(&data[row * columns], columns);
}

const Matrix& Matrix::operator*=(int factor)
{
	for (size_t i = 0; i < rows*columns; ++i) 
		data[i] *= factor;

	return *this;
}

bool Matrix::operator==(const Matrix& other) const
{
	if(this == &other)
		return true;

	if (rows != other.rows)
		return false;

	if (columns != other.columns)
		return false;

	for (size_t i = 0; i < rows*columns; ++i)
		if (data[i] != other.data[i])
			return false;

	return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
	return !(*this == other);
}