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

//funkcja pobierajaca kolejny znak z ciagu wejsciowego
bool Scanner::nextChar(){
  currentPosition++;
  if(currentPosition==inputSource.size())
  return false;
  currentChar = inputSource.at(currentPosition);
  return true;
}

//funkcja zwracajaca kolejny atom leksykalny (token)
Token* Scanner::nextSymbol(){
  Token* token;
  if(currentPosition+1==inputSource.size()) //koniec ciagu znakow
    return NULL;
  if(!nextChar())
  return NULL;
  while(isspace(currentChar)){    //wyczyszczenie bialych znakow
    if(!nextChar())
    return NULL;
  }
  if(currentChar=='"') {  //mozliwy token: Value
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
  if(currentChar=='<')  //mozliwe tokeny: Open_Start_Tag, Open_End_Tag, Open_Comment_Tag, Open_Doctype_Tag
  {
    nextChar();
    if(currentChar=='/')  //mozliwy token: Open_End_Tag
    {
      token = new Token(Open_End_Tag);
      tokens.push_back(token);
      return token;
    }
    else if(currentChar=='!') //mozliwe tokeny: Open_Comment_Tag, Open_Doctype_Tag
    {
      previousPosition=currentPosition;
      text="";
      for(int i=0;i<MAXLENGTH;i++)
      {
        nextChar();
        text+=currentChar;
      }
      if(text.compare(0,2,"--")==0) //mozliwy token: Open_Comment_Tag
      {
        currentPosition = previousPosition + 2;
        token = new Token(Open_Commment_Tag);
        tokens.push_back(token);
        return token;
      }
      else if(text.compare("DOCTYPE")==0) //mozliwy token: Open_Doctype_Tag
      {
        currentPosition=previousPosition + 7;
        token = new Token(Open_Doctype_Tag);
        tokens.push_back(token);
        return token;
      }
      else{
        cout<<"Error in Scanner. Invalid sign."<<endl;
        return NULL;
      }
    }
    else  //mozliwy token: Open_Start_Tag
    {
      currentPosition--;
      token = new Token(Open_Start_Tag);
      tokens.push_back(token);
      return token;
    }
  }
  if(currentChar=='>')  //mozliwy token: Close_Tag
  {
    token = new Token(Close_Tag);
    tokens.push_back(token);
    return token;
  }
  if(currentChar=='/')  //mozliwy token: Close_Self_Closing_Tag
  {
    nextChar();
    if(currentChar=='>')  //mozliwy token: Close_Self_Closing_Tag
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
  if(currentChar=='=')  //mozliwy token: Equals_Sign
  {
    if(!isText())
    {
      token = new Token(Equals_Sign);
      tokens.push_back(token);
      return token;
    }
  }
  if(currentChar=='-')  //mozliwy token: Close_Comment_Tag
  {
    nextChar();
    if(currentChar=='-')  //mozliwy token: Close_Comment_Tag
    {
      nextChar();
      if(currentChar=='>')  //mozliwy token: Close_Comment_Tag
      {
        token = new Token(Close_Comment_Tag);
        tokens.push_back(token);
        return token;
      }
      else
      {
        cout<<"Error in Scanner. Invalid sign."<<endl;
        return NULL;
      }
    }
    else
    {
      currentChar='-';
      currentPosition--;
    }
  }
  //mozliwy token: Text
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

//funkcja sprawdzajaca czy aktualny znak jest tekstem
bool Scanner::isText(){
  switch(currentChar)
  {
    case ' ':return false;
    case '<':return false;
    case '>':return false;
    case '"':return false;
    case '=':
    {
      int i=0;
      nextChar();
      while(isspace(currentChar)){  //wyczyszczenie bialych znakow
        nextChar();
        i++;
      }
      if(currentChar!='"')  //sprawdzenie czy znak '=' nie jest tokenem: Equals_Sign
      {
        currentPosition=currentPosition-i-1;
        currentChar='=';
        return true;
      }
      else
      {
        currentPosition=currentPosition-i-1;
        currentChar='=';
        return false;
      }
    }
    case '/': //sprawdzenie czy nie pojawil sie token : Close_Self_Closing_Tag: '/>'
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
    case '-': //sprawdzenie czy nie pojawil sie token : Close_Comment_Tag: '-->'
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

//funkcja sprawdzajaca czy aktualny znak jest wartoscia
bool Scanner::isValue(){
  if(currentChar=='\\') //sprawdznie czy nie pojawil sie znak '\"' oznaczajacy cudzyslow z tokenie: Value
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
  else if(currentChar!='"') //sprawdzenie czy nie konczy sie token: Value znakiem '"'
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
