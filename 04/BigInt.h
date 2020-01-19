/*BigInt*/

#include <algorithm>
#include <string>
#include <cstdint>

class BigInt
{
	private:
		size_t size;
		char* data;
		bool isNegative;
	public:
	
		BigInt():
			size(1),
			data(new char[1]),
			isNegative(false)
		{data[0] = '0';}
	
		BigInt(const std::string& str)
		{
			size_t offset = 0;

			if (str[0] == '-')
			{
				isNegative = true;
				offset = 1;
			}
			else
			{
				isNegative = false;
			}
			size = str.size() - offset;
			data  = new char[size];

			for (size_t i = offset; i < str.size(); i++)
				data[i - offset] = str[i];
		}

		BigInt(int Int) : BigInt(std::to_string(Int)) {}
		BigInt(int64_t Int) : BigInt(std::to_string(Int)) {}

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

		BigInt operator+(const BigInt& other) const
		{
			if ((isNegative == other.isNegative) && !isNegative)
			{
				BigInt tmp;

				int max_size = std::max(size, other.size) + 1;
				int* sum = new int[max_size];

				for (size_t i = 0; i < max_size; i++)
					sum[i] = 0;

				for (size_t i = 0; i < max_size - 1; i++)
				{
					if (size >= 1 + i)
						sum[max_size - 1 - i] += (data[size - 1 - i] - '0');
					
					if (other.size >= 1 + i)
						sum[max_size - 1 - i] += (other.data[other.size - 1 - i] - '0');
					
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
				delete [] sum;
				return tmp;
			}
			// Just to avoid warning
			return 666;
		}

		BigInt operator+(const int& Int) const;

		friend BigInt operator+(const int& Int, const BigInt& bigInt);

		BigInt operator-(const BigInt& other) const
		{
			// Just to avoid warning
			return 666;	
		}

		BigInt operator-(const int& Int) const;

		friend BigInt operator-(const int& Int, const BigInt& bigInt);
		
};

std::ostream& operator<<(std::ostream& out, const BigInt& value)
{
	if (value.isNegative)
		out << '-';

	for (size_t i = 0; i < value.size; i++)
		out << value.data[i];

	return out;
}