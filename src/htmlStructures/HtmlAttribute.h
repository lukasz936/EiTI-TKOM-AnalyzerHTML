#ifndef HTML_ATTRIBUTE_H
#define HTML_ATTRIBUTE_H
#include <iostream>

class HtmlAttribute{
  std::string name;
  std::string value;
public:
  HtmlAttribute();
  HtmlAttribute(std::string, std::string);
  ~HtmlAttribute();
};

#endif
