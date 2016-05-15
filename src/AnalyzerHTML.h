#ifndef ANALYZER_HTML_H
#define ANALYZER_HTML_H

#include "errors/Error.h"
#include "fileReader/FileReader.h"
#include "scanner/Scanner.h"
#include "parser/Parser.h"

class AnalyzerHTML{
  Error error;
public:
  AnalyzerHTML(int, char**);
};

#endif
