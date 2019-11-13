/*Calcultor*/

#include <iostream>
#include <stdexcept>
//#include <string>
//#include <memory>
#include <fstream>

using namespace std;

enum class Operation
{
	INVALID,
	VALUE,
	PLUS,
	MINUS,
	TIMES,
	OVER,
	EoF
};

class Symbol
{
public:

	void set(const char* str)
	{
		this->str = str;
		value = 0;
		current = Operation::INVALID;
	}

	int getSymbol()
	{
		while (const auto simbol = *str++)
		{
			switch (simbol)
			{
				case ' ': continue;
				case '+': current = Operation::PLUS; return 0;
				case '-': current = Operation::MINUS; return 0;
				case '*': current = Operation::TIMES; return 0;
				case '/': current = Operation::OVER; return 0;
			}

			if (simbol >= '0' && simbol <= '9')
			{
				value = simbol - '0';
				while (*str >= '0' && *str <= '9')
				{
					value = value * 10 + (*str++) - '0';
				}
				current = Operation::VALUE;
				return value;
			}

			throw invalid_argument("Error");
		}

		current =  Operation::EoF;
		return 0;
	}

	Operation getCurrent() { return current; }
	int getValue() { return value; }
	
private:

	const char* str;
	Operation current;
	int value;

};

class Calculator
{
public:

	int calculate(const char* str)
	{
		symbol.set(str);
		return calculator();
	}

private:

	Symbol symbol;

	int calculator()
	{
		int result = resTimes();

		while (symbol.getCurrent() == Operation::PLUS || symbol.getCurrent()  == Operation::MINUS)
		{
			if (symbol.getCurrent()  == Operation::PLUS)
			{
				result += resTimes();
			}
			else
			{
				result -= resTimes();
			}
		}
		return result;
	}

	int resTimes()
	{
		int result = getSign();

		while (symbol.getCurrent()  == Operation::TIMES || symbol.getCurrent()  == Operation::OVER)
		{
			if (symbol.getCurrent()  == Operation::OVER)
			{
				int number = getSign();
				if (number == 0)
				{
					throw invalid_argument("Error");
				}
				else
				{
					result /= number;
				}
			}
			else
			{
				result *= getSign();
			}
		}

		return result;
	}
	
	int getSign()
	{
		int number = symbol.getSymbol();

		if(symbol.getCurrent() != Operation::VALUE && symbol.getCurrent() != Operation::MINUS)
		{
			throw invalid_argument("Error");
		}

		if(symbol.getCurrent() == Operation::VALUE)
		{
			symbol.getSymbol();
			return number;
		}

		else if (symbol.getCurrent() == Operation::MINUS)
		{
			number = symbol.getSymbol();
			if (symbol.getCurrent() == Operation::VALUE)
			{
				symbol.getSymbol();
				return -1 * number;
			}
			else
			{
				throw invalid_argument("Error");
			}
		}
		return 0;
	}
};

int main(int argc, char **argv){

	//const char* str{"2 + 3 * 4 / 2 - -2"};
	std::cout << "File:" << argv[1] << std::endl;

	char str[50];

	const char* err{"error"};

	ifstream fin(argv[1]);
	while (fin){
		try
		{
			Calculator calc;
			fin.getline(str, 50);
			std::cout << "calc " << str << " = " << calc.calculate(str) << std::endl;
		}
		catch(invalid_argument&)
		{
			cout << err << endl;
			//return 1;
		}
	}
	fin.close();
	
	return 0;
}