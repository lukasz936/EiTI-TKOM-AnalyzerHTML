#include "HtmlElement.h"
#include <iostream>

HtmlElement::HtmlElement(){

}

HtmlElement::HtmlElement(std::string name ,std::vector<HtmlAttribute*> attributes,std::string text,std::string comment,std::vector<HtmlElement*> elements){
  this->name=name;
  this->attributes=attributes;
  this->text=text;
  this->comment=comment;
  this->elements=elements;
}

HtmlElement::~HtmlElement(){

    for(int i=0;i<this->attributes.size();i++)
    {
      delete attributes.at(i);
    }

    for(int i=0;i<this->elements.size();i++)
    {
      delete elements.at(i);
    }
}

std::string HtmlElement::getName()
{
  return this->name;
}
std::vector<HtmlAttribute*> HtmlElement::getAttributes()
{
  return this->attributes;
}
std::string HtmlElement::getText()
{
  return this->text;
}
std::string HtmlElement::getComment()
{
  return this->comment;
}
std::vector<HtmlElement*> HtmlElement::getElements()
{
  return this->elements;
}
