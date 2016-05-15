#include "../tokens/Token.h"
#include "../scanner/Scanner.h"
#include <vector>
class Parser{
  Scanner* scanner;
  std::vector<Token*>* tokens;
  int i;
public:
  Parser(Scanner* scanner);
  void start();
  void parseHtml();

};
