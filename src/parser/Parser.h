#ifndef PARSER_H
#define PARSER_H

#include "../tokens/Token.h"
#include "../scanner/Scanner.h"
#include "../htmlStructures/Html.h"
#include <vector>
class Parser{
  Error error;
  Scanner* scanner;
  std::vector<Token*>* tokens;
  Html* html;
public:
  Parser(Scanner* scanner);
  ~Parser();
  void start();
  Html* parseHtml();
  HtmlElement* parseElement();
  HtmlAttribute* parseAttribute();
  Html* getHtml();
  std::vector<HtmlElement*> searchElements(HtmlElement*, std::string,std::string,std::string);

};

#endif
