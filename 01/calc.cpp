/*Calculator*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
//#include <memory>
#include <fstream>
#include <array>
#include <sstream>


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

	void set(const std::string& str)
	{
		size_t len = str.size() + 1;
		this->str = new char[len];
		std::memcpy(this->str, str.data(), len);
		// this->str[len] = 0;
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

			throw invalid_argument("invalid input symbol");
			//throw "invalid input symbol";
		}

		current =  Operation::EoF;
		return 0;
	}

	Operation getCurrent() { return current; }
	int getValue() { return value; }
	
private:

	char* str;
	Operation current;
	int value;

};

class Calculator
{
public:

	int calculate(const std::string& str)
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
					throw invalid_argument("division by 0");
					//throw "division by 0";
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
			throw invalid_argument("invalid input symbol combination");
			//throw "invalid input symbol combination";
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
				throw invalid_argument("invalid input symbol combination");
				//throw "invalid input symbol combination";
			}
		}
		return 0;
	}
};

int main(int argc, char **argv){

	const auto res = std::array<const char*, 7> { "2", "-2", "10", "0", "division by 0", "invalid input symbol", "invalid input symbol combination"  };
	int i = 0;
	//const char* str{"2 + 3 * 4 / 2 - -2"};

	if (argc < 2)
    {
        std::cerr << "No arguments" << '\n';
        return 1;
    }


	std::cout << "File:" << argv[1] << std::endl;

	std::string str;

	//const char* err{"error"};

	ifstream fin(argv[1]);
	while (std::getline(fin, str)){
		try
		{
			Calculator calc;
			//std::cout << "str:" << str << std::endl;
			// fin.getline(str, 50);
			//getline(fin,str);
			std::ostringstream ost;
    		ost << calc.calculate(str);
			std::cout << "calc " << str << " = " << ost.str() << std::endl << "    expected " << res[i] << std::endl << "    result " <<  ((ost.str() == res[i])?"True":"False")  << std::endl;
			i++;
		}
		catch(exception &err)
		{
			std::ostringstream ost;
			ost << err.what();
			cout << "calc " << str << " = " << ost.str() << endl << "    expected " << res[i] << endl << "    result " <<  ((ost.str() == res[i])?"True":"False") << std::endl;
			//cout << err.what() << " " << (err.what() == res[i]) << endl;
			i++;
			//return 1;
		}
		//catch (const std::string &erStr) 
    	//{
         	//std::cout << erStr << std::endl;
    	//}
	}
	//fin.close();
	
	return 0;
}
