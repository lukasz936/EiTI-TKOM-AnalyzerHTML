#include "Token.h"
#include <string>

using namespace std;

Token::Token(TokenType type, string content){
  this->type = type;
  this->content = content;
}

Token::Token(TokenType type){
  this->content = "";
  this->type = type;
}

Token::~Token(){
}

TokenType Token::getTokenType(){
  return this->type;
}

string Token::getContent(){
  return this->content;
}
