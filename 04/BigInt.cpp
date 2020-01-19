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

		BigInt operator+(const BigInt& other)
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
		}

		BigInt operator+(const int& Int);

		friend BigInt operator+(const int& Int, const BigInt& bigInt);

		BigInt operator-(const BigInt& other)
		{
			
		}

		BigInt operator-(const int& Int);

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

int main(){

	BigInt a = 1;
	BigInt b = a;
	BigInt c = a + b + 2;

	return 0;
}