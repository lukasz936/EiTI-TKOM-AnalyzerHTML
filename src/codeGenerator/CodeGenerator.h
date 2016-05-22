#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "../errors/Error.h"
#include "../htmlStructures/Html.h"
#include "../parser/Parser.h"
#include <iostream>

class CodeGenerator{
 Error error;
 Parser* parser;
 std::string stringJSON;
public:
  CodeGenerator();
  ~CodeGenerator();
  std::string getStringJSON();
  void start(Parser*);
  void addFirstCharacters();
  void addLastCharachters();
  void addObject(std::string,std::string,std::string,std::string,std::string);
};

#endif
