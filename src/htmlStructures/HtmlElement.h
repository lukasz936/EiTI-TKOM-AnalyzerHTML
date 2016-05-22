#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H
#include <vector>
#include <iostream>
#include "HtmlAttribute.h"

class HtmlElement{
  std::string name;
  std::vector<HtmlAttribute*> attributes;
  std::string text;
  std::string comment;
  std::vector<HtmlElement*> elements;
public:
  HtmlElement();
  HtmlElement(std::string,std::vector<HtmlAttribute*>,std::string,std::string,std::vector<HtmlElement*>);
  ~HtmlElement();
  std::string getName();
  std::vector<HtmlAttribute*> getAttributes();
  std::string getText();
  std::string getComment();
  std::vector<HtmlElement*> getElements();
};

#endif
