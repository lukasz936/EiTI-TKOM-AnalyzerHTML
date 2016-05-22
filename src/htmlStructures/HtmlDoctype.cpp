#include "HtmlDoctype.h"

HtmlDoctype::HtmlDoctype(){

}

HtmlDoctype::HtmlDoctype(std::vector<std::string> texts, std::vector<std::string> values){
  this->texts=texts;
  this->values=values;
}

HtmlDoctype::~HtmlDoctype(){

}

std::vector<std::string> HtmlDoctype::getTexts()
{
  return this->texts;
}

std::vector<std::string> HtmlDoctype::getValues()
{
  return this->values;
}
