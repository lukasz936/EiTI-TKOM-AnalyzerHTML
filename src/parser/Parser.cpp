#include "Parser.h"

using namespace std;

Parser::Parser(Scanner* scanner)
{
  this->scanner=scanner;
  this->tokens=scanner->getPointerOnTokens();
  this->i=0;
}

void Parser::start()
{
  Token* token;
  while(true)
  {
    token=scanner->nextSymbol();
    if(token==NULL)
      break;
    
  }
}
