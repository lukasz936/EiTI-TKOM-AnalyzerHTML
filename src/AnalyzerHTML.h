#ifndef ANALYZER_HTML_H
#define ANALYZER_HTML_H

#include "fileReader/FileReader.h"
#include "scanner/Scanner.h"
#include "parser/Parser.h"
#include "codeGenerator/CodeGenerator.h"
#include "fileCreator/FileCreator.h"

class AnalyzerHTML{
private:
  void startGenerateCode(int, char**,Parser*, CodeGenerator*);
public:
  AnalyzerHTML(int, char**);
};

#endif
