#ifndef HTML_H
#define HTML_H
#include "HtmlDoctype.h"
#include "HtmlElement.h"

class Html{
  HtmlDoctype* doctype;
  HtmlElement* element;
public:
  Html();
  Html(HtmlDoctype*,HtmlElement*);
  ~Html();
};
#endif
