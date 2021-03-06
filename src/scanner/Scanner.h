#ifndef SCANNER_H
#define SCANNER_H

#include "../tokens/Token.h"
#include <iostream>
#include <vector>
#define MAXLENGTH 7

class Scanner{
  std::vector<Token*> tokens;
  std::string inputSource;
  int currentPosition;
  int previousPosition;
  std::string text;
  char currentChar;
  bool nextChar();
  bool isText();
  bool isValue();

public:
  Scanner();
  Scanner(std::string inputSource);
  ~Scanner();
  Token* nextSymbol();
  std::vector<Token*>* getPointerOnTokens();
};

#endif
