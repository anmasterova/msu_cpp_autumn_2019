/*Calculator*/

#include <sstream>
#include <string>
#include <stdexcept>

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

bool checkSymbolAsOperation(char c, Operation& operation) 
{
  switch (c) 
  {
    case '+':
      operation = Operation::PLUS;
      break;
    case '-':
      operation = Operation::MINUS;
      break;
    case '*':
      operation = Operation::TIMES;
      break;
    case '/':
      operation = Operation::OVER;
      break;
    default:
      return false;
  }
  return true;
}

class Symbol 
{
 public:
  void set(const std::string& str) 
  {
    this->sstr = std::stringstream(str);
    value = 0;
    current = Operation::INVALID;
  }

  int getSymbol() 
  {
    while (sstr.good()) 
    {
      sstr >> std::ws;
      const char symbol = sstr.peek();
      if (checkSymbolAsOperation(symbol, current)) 
      {
        sstr.ignore();
        return 0;
      }
      if (std::isdigit(symbol)) 
      {
        sstr >> value;
        current = Operation::VALUE;
        return value;
      }
      throw std::invalid_argument("invalid input symbol");
    }

    current = Operation::EoF;
    return 0;
  }

  Operation getCurrent() { return current; }
  int getValue() { return value; }

 private:
  std::stringstream sstr;
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

    while (symbol.getCurrent() == Operation::PLUS || symbol.getCurrent() == Operation::MINUS) 
    {
      if (symbol.getCurrent() == Operation::PLUS) 
        result += resTimes();
      else 
       result -= resTimes();
    }
    return result;
  }

  int resTimes() 
  {
    int result = getSign();

    while (symbol.getCurrent() == Operation::TIMES || symbol.getCurrent() == Operation::OVER) 
    {
      if (symbol.getCurrent() == Operation::OVER) 
      {
        int number = getSign();
        if (number == 0) 
        {
          throw std::invalid_argument("division by 0");
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

    if (symbol.getCurrent() != Operation::VALUE && symbol.getCurrent() != Operation::MINUS) 
    {
      throw std::invalid_argument("invalid input symbol combination");
    }

    if (symbol.getCurrent() == Operation::VALUE) 
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
        throw std::invalid_argument("invalid input symbol combination");
      }
    }
    return 0;
  }
};
