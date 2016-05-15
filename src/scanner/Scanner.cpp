#include "Scanner.h"
#include <string>

using namespace std;

Scanner::Scanner(){
  this->inputSource="";
  this->currentPosition=-1;
  this->currentChar=' ';
}

Scanner::Scanner(string inputSource){
  this->inputSource=inputSource;
  this->currentPosition=-1;
  this->currentChar=' ';
}

Scanner::~Scanner(){
  for(int i=0;i<tokens.size();i++)
  {
    delete tokens.at(i);
  }
}

void Scanner::nextChar(){
  currentPosition++;
  currentChar = inputSource.at(currentPosition);
}

Token* Scanner::nextSymbol(){
  Token* token;
  if(currentPosition+1==inputSource.size())
  return NULL;
  nextChar();
  while(isspace(currentChar)){
    nextChar();
  }
  if(currentChar=='"') {
    text="";
    nextChar();
    while(isValue())
    {
      text+=currentChar;
      nextChar();
    }
    token = new Token(Value,text);
    tokens.push_back(token);
    return token;
  }
  if(currentChar=='<')
  {
    nextChar();
    if(currentChar=='/')
    {
      token = new Token(Open_End_Tag);
      tokens.push_back(token);
      return token;
    }
    else if(currentChar=='!')
    {
      previousPosition=currentPosition;
      text="";
      for(int i=0;i<MAXLENGTH;i++)
      {
        nextChar();
        text+=currentChar;
      }
      if(text.compare(0,2,"--")==0)
      {
        currentPosition = previousPosition + 2;
        token = new Token(Open_Commment_Tag);
        tokens.push_back(token);
        return token;
      }
      else if(text.compare("DOCTYPE")==0)
      {
        currentPosition=previousPosition + 7;
        token = new Token(Open_Doctype_Tag);
        tokens.push_back(token);
        return token;
      }
      else{
        error.show(SCANNER_INVALID_SIGN);
        return NULL;
      }
    }
    else
    {
      currentPosition--;
      token = new Token(Open_Start_Tag);
      tokens.push_back(token);
      return token;
    }
  }
  if(currentChar=='>')
  {
    token = new Token(Close_Tag);
    tokens.push_back(token);
    return token;
  }
  if(currentChar=='/')
  {
    nextChar();
    if(currentChar=='>')
    {
      token = new Token(Close_Self_Closing_Tag);
      tokens.push_back(token);
      return token;
    }
    else{
      currentChar='/';
      currentPosition--;
    }
  }
  if(currentChar=='=')
  {
    token = new Token(Equals_Sign);
    tokens.push_back(token);
    return token;
  }
  if(currentChar=='-')
  {
    nextChar();
    if(currentChar=='-')
    {
      nextChar();
      if(currentChar=='>')
      {
        token = new Token(Close_Comment_Tag);
        tokens.push_back(token);
        return token;
      }
      else
      {
        error.show(SCANNER_INVALID_SIGN);
        return NULL;
      }
    }
    else
    {
      currentChar='-';
      currentPosition--;
    }
  }
  text=currentChar;
  nextChar();
  while(isText())
  {
    text+=currentChar;
    nextChar();
  }
  currentPosition--;
  token = new Token(Text,text);
  tokens.push_back(token);
  return token;
}

bool Scanner::isText(){
  switch(currentChar)
  {
    case ' ':return false;
    case '=':return false;
    case '<':return false;
    case '>':return false;
    case '"':return false;
    case '/':
    {
      nextChar();
      if(currentChar=='>')
      {
        currentPosition=currentPosition-1;
        currentChar='/';
        return false;
      }
      else{
        currentPosition=currentPosition-1;
        currentChar='/';
        return true;
      }
    }
    case '-':
    {
      nextChar();
      if(currentChar=='-')
      {
        nextChar();
        if(currentChar=='>')
        {
          currentPosition=currentPosition-2;
          currentChar='-';
          return false;
        }
        else
        {
          currentPosition=currentPosition-2;
          currentChar='-';
          return true;
        }
      }
      else
      {
        currentPosition=currentPosition-1;
        currentChar='-';
        return true;
      }
    }
    default:
    {
      return true;
    }
  }
}

bool Scanner::isValue(){
  if(currentChar=='\\')
  {
    nextChar();
    if(currentChar=='"')
    {
      return true;
    }
    else{
      currentChar='\\';
      currentPosition--;
      return true;
    }
  }
  else if(currentChar!='"')
  {
    return true;
  }
  else{
    return false;
  }
}

vector<Token*>* Scanner::getPointerOnTokens(){
  return &(this->tokens);
}
