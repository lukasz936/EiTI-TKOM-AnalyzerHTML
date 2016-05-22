#include "HtmlAttribute.h"

HtmlAttribute::HtmlAttribute(){

}

HtmlAttribute::HtmlAttribute(std::string name, std::string value){
  this->name=name;
  this->value=value;
}

HtmlAttribute::~HtmlAttribute(){

}

std::string HtmlAttribute::getName()
{
  return this->name;
}

std::string HtmlAttribute::getValue()
{
  return this->value;
}
