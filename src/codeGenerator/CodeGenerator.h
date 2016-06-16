#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "../htmlStructures/Html.h"
#include "../parser/Parser.h"
#include <iostream>

class CodeGenerator{
 Parser* parser;
 std::string stringJSON;
public:
  CodeGenerator();
  ~CodeGenerator();
  std::string getStringJSON();
  void start(Parser*, char*, char*);
  void addFirstCharacters();
  void addLastCharachters();
  void addObject(std::string,std::string,std::string,std::string,std::string);
  bool checkFilter(char*,char*,std::string,std::string);
};

#endif
