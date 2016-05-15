#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <string>

class Token{
private:
  TokenType type;
  std::string content;
public:
  Token(TokenType, std::string);
  Token(TokenType);
  ~Token();
  TokenType getTokenType();
  std::string getContent();
};

#endif
