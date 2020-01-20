#include <array>
#include <fstream>
#include <iostream>

#include "Calculator.h"

void TestFileExecution() {
  std::cout << "#### TestFileExecution ####\n";
  const std::array<const char*, 7> res = {"2",
                                          "-2",
                                          "10",
                                          "0",
                                          "division by 0",
                                          "invalid input symbol",
                                          "invalid input symbol combination"};
  char fileName[] = "test.txt";
  { /* Create and fill file with data */
    std::string fileInput = "2\n-2\n2 + 3 * 4 / 2 - -2\n-2 - -2\n2 / 0\n2 + b";
    std::ofstream fout(fileName);
    fout << fileInput;
  }
  int i = 0;
  std::string str;
  std::ifstream fin(fileName);
  while (std::getline(fin, str)) {
    try {
      Calculator calc;
      std::ostringstream ost;
      ost << calc.calculate(str);
      std::cout << "calc " << str << " = " << ost.str() << '\n'
                << " expected " << res[i] << '\n'
                << " result " << ((ost.str() == res[i]) ? "True" : "False")
                << '\n';
    } catch (std::exception& err) {
      std::ostringstream ost;
      ost << err.what();
      std::cout << ost.str() << '\n'
                << " expected " << res[i] << '\n'
                << " result " << ((ost.str() == res[i]) ? "True" : "False")
                << '\n';
    }
    i++;
  }
}

void TestOperation(char op, std::string opName, int (*f)(int, int)) {
  std::cout << "#### Test" << opName << " ####\n";
  for (int i = -12; i <= 12; i += 3)
    for (int j = -6; j <= 6; j += 3) {
      try {
        Calculator calc;
        std::ostringstream ost;
        ost << i << " " << op << " " << j;
        int result = calc.calculate(ost.str());
        std::cout << "calc " << i << " " << op << " " << j << " = " << ost.str()
                  << '\n'
                  << " expected " << f(i, j) << '\n'
                  << " result " << ((result == f(i, j)) ? "True" : "False")
                  << '\n';
      } catch (std::exception& err) {
        std::ostringstream ost;
        ost << err.what();
        std::cout << ost.str() << std::endl
                  << " expected " << f(i, j) << '\n'
                  << " result False" << '\n';
      }
    }
}

int main(int argc, char** argv) {
  TestOperation('+', "Sum", [](int x, int y) { return x + y; });
  TestOperation('-', "Diff", [](int x, int y) { return x - y; });
  TestOperation('*', "Times", [](int x, int y) { return x * y; });

  TestFileExecution();
  return 0;
}