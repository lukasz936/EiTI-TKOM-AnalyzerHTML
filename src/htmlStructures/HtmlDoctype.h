#ifndef HTML_DOCTYPE_H
#define HTML_DOCTYPE_H
#include <vector>
#include <iostream>
class HtmlDoctype{
  std::vector<std::string>* texts;
  std::vector<std::string>* values;
public:
  HtmlDoctype();
  HtmlDoctype(std::vector<std::string>*,std::vector<std::string>*);
  ~HtmlDoctype();
};

#endif
