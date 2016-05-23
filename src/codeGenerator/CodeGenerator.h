#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "../errors/Error.h"
#include "../htmlStructures/Html.h"
#include "../parser/Parser.h"
#include "CodeGeneratorType.h"
#include <iostream>

class CodeGenerator{
 Error error;
 CodeGeneratorType codeGeneratorType;
 Parser* parser;
 std::string stringJSON;
public:
  CodeGenerator();
  ~CodeGenerator();
  void setCodeGeneratorType(char*);
  std::string getStringJSON();
  void start(Parser*, char*);
  void addFirstCharacters();
  void addLastCharachters();
  void addObject(std::string,std::string,std::string,std::string,std::string);
  bool checkFilter(std::string, std::string);
};

#endif
