/*BigInt*/

#include <iostream>
#include <cstring>
#include <cassert>

class BigInt
{
	private:
		size_t size;
		char* data;
		bool isNegative;
	public:
	
		BigInt():
			size(0),
			data(nullptr),
			isNegative(false)
		{}

		BigInt(int Int): 
			isNegative(Int < 0)
		{
			std::string tmp;

			if (isNegative) 
				tmp = std::to_string(-Int);
			else 
				tmp = std::to_string(Int);

			size = tmp.length();
			data = new char [size];

			for (size_t i = 0; i < size; i++)
				data[i] = tmp[i];
		}
	


		BigInt(std::string& str)
		{
			std::string tmp;

			if (str[0] == '-')
			{
				isNegative = true;
				size = str.length() - 1;
				tmp = str.substr(1, size);
			}
			else
			{
				isNegative = false;
					size = str.length();
					tmp = str;
			}
	
			data  = new char[size];

			for (size_t i = 0; i < size; i++ )
				data[i] = tmp[i];
		}

		~BigInt()
		{delete[] data;}



		BigInt(const BigInt& copied): 
			size(copied.size),
			data(new char [copied.size]),
			isNegative(copied.isNegative)
		{std::copy(copied.data, copied.data + size, data);}

		BigInt& operator=(const BigInt& copied)
		{
			if (this == &copied)
				return *this;

			char* ptr = new char[copied.size];
			
			delete[] data;

			data = ptr;
			isNegative = copied.isNegative;
			size = copied.size;
			
			std::copy(copied.data, copied.data + size, data);

			return *this;
		}



		BigInt(BigInt&& moved):
			size(moved.size),
			data(moved.data),
			isNegative(moved.isNegative)
		{
			moved.size = 0;
			moved.data = nullptr;
			moved.isNegative = false;
		}


		BigInt& operator=(BigInt&& moved)
		{
			if (this == &moved)
				return *this;

			delete [] data;

			size = moved.size;
			data = moved.data;
			isNegative = moved.isNegative;
			
			moved.size = 0;
			moved.data = nullptr;
			moved.isNegative = false;
			
			return *this;
		}
	



		friend std::ostream& operator<<(std::ostream& out, const BigInt& value);
	


		BigInt operator-() const 
		{
			BigInt tmp (*this);
			tmp.isNegative = !isNegative;
			return tmp;
		}


		bool operator==(const BigInt& other) const
		{
			if (this == &other)
				return true;

			if (isNegative == other.isNegative && size == other.size)
			{
				for(size_t i = 0; i < size; i++)
					if (data[i] != other.data[i])
						return false;
				return true;
			}

			return false;
		}

		bool operator!=(const BigInt& other) const
		{return !(*this == other);}

		bool operator<(const BigInt& other) const
		{
			if (this == &other)
				return false;

			if (isNegative != other.isNegative)
				return isNegative;
			
			if (size != other.size)
			{
				if (isNegative) 
					return (size > other.size);
				else 
					return (size < other.size);
			}

			for (int i = 0; i < size; i++) 
				if (data[i] != other.data[i]) 
		    	{
					if (isNegative) 
						return (data[i] > other.data[i]);
					else 
						return (data[i] < other.data[i]);
				}

			return false;
		}

		bool operator<=(const BigInt& other) const
		{return ((*this < other) || (*this == other));}

		bool operator>(const BigInt& other) const
		{return !(*this <= other);}

		bool operator>=(const BigInt& other) const
		{return !(*this < other);}

		BigInt plus(const BigInt& first, const BigInt& second)
		{
			BigInt tmp;
			int max_size = std::max(first.size, second.size) + 1;
			int* sum = new int[max_size];
			
			for (size_t i = 0; i < max_size; i++)
				sum[i] = 0;

			for (size_t i = 0; i < max_size - 1; i++)
			{
				if (first.size >= 1 + i)
					sum[max_size - 1 - i] += (first.data[first.size - 1 - i] - '0');
				
				if (second.size >= 1 + i)
					sum[max_size - 1 - i] += (second.data[second.size - 1 - i] - '0');
				sum[max_size - 2 - i] = sum[max_size - 1 - i] / 10;
				sum[max_size - 1 - i] = sum[max_size - 1 - i] % 10;
			}
			if (sum[0] == 0)
			{
				tmp.size = max_size - 1;
				tmp.data = new char[tmp.size];
				for (size_t i = 0; i < tmp.size; i++)
					tmp.data[i] = sum[i + 1] + '0';
			}
			else
			{
				tmp.size = max_size;
				tmp.data = new char[tmp.size];
				for (size_t i = 0; i < tmp.size; i++)
					tmp.data[i] = sum[i] + '0';
			}
			delete[] sum;
			return tmp;
		}

		BigInt minus(const BigInt& first, const BigInt& second)
		{
			if (second > first)
					return -minus(second, first);

			int* diff = new int[first.size];

			for (size_t i = 0; i < first.size; i++)
				diff[i] = first.data[i] - '0';

			for (size_t i = 0; i < first.size - 1; i++)
			{
				if (second.size >= i + 1)
					diff[first.size - 1 - i] -= second.data[second.size - 1 - i] - '0';
				
				if (diff[first.size - 1 - i] < 0)
				{
					diff[first.size - 1 - i] += 10;
					diff[first.size - 2 - i] -= 1;
				}
			}

			if (second.size == first.size)
				diff[0] -= second.data[0] - '0';

			size_t diffSize = first.size;

			for (size_t i = 0; i < first.size; i++)
			{
				if (diff[i] == 0)
					diffSize -= 1;
				else
					break;
			}

			BigInt tmp = first;
			tmp.size = diffSize;
			for (size_t i = 0; i < tmp.size; i++)
				tmp.data[tmp.size - 1 - i] = diff[first.size - 1 - i] + '0';
			delete[] diff;
			return tmp;
		}

		BigInt operator+(const BigInt& other)
		{
			if ((isNegative == other.isNegative) && !isNegative)
				return plus(*this, other);	
			else if ((isNegative == other.isNegative) && isNegative)
			{
				BigInt tmp = plus(*this, other);
				tmp.isNegative = true;
				return tmp;
			}
			else
			{
				BigInt tmp;
				
				if (size > other.size)
				{
					tmp = minus(*this, other);
					tmp.isNegative = isNegative;
				}
				else
				{
					tmp = minus(other, *this);
					tmp.isNegative = other.isNegative;
				}

				return tmp;
			}
		}

		BigInt operator+(const int& Int)
		{
			BigInt tmp = Int;
			return (*this + tmp);
		}

		friend BigInt operator+(const int& Int, const BigInt& bigInt);

		BigInt operator-(const BigInt& other)
		{
			if ((isNegative == other.isNegative) && !isNegative)
				return minus(*this, other);	
			else if ((isNegative == other.isNegative) && isNegative)
			{
				BigInt tmp = plus(-(*this), -(other));
				tmp.isNegative = true;
				return tmp;
			}
			else
			{
				BigInt tmp;
				
				if (!isNegative)
				{
					tmp = plus(-(*this), other);
					tmp.isNegative = true;
				}
				else
				{
					tmp = plus(*this, -(other));
					tmp.isNegative = true;				
				}

				return tmp;
			}
		}

		BigInt operator-(const int& Int)
		{
			BigInt tmp = Int;
			return (*this - tmp);
		}

		friend BigInt operator-(const int& Int, const BigInt& bigInt);
		
};

std::ostream& operator<<(std::ostream& out, const BigInt& value)
			{
				if (value.isNegative)
					out << '-';
			
				for (size_t i = 0; i < value.size; i++)
					out << value.data[i];
			
				out << std::endl;
			
				return out;
			}

BigInt operator+(const int& Int, const BigInt& bigInt)
{
	BigInt tmp = Int;
	return (tmp + bigInt);
}

BigInt operator-(const int& Int, const BigInt& bigInt)
{
	BigInt tmp = Int;
	return (tmp - bigInt);
}
