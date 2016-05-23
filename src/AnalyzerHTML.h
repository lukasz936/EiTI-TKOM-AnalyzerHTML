#ifndef ANALYZER_HTML_H
#define ANALYZER_HTML_H

#include "errors/Error.h"
#include "fileReader/FileReader.h"
#include "scanner/Scanner.h"
#include "parser/Parser.h"
#include "codeGenerator/CodeGenerator.h"
#include "fileCreator/FileCreator.h"


class AnalyzerHTML{
  Error error;
public:
  AnalyzerHTML(int, char**);
};

#endif
