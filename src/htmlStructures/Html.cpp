#include "Html.h"

Html::Html(){

}

Html::Html(HtmlDoctype* doctype, HtmlElement* element){
  this->doctype=doctype;
  this->element=element;
}

Html::~Html(){
  delete this->doctype;
  delete this->element;
}

HtmlDoctype* Html::getDoctype()
{
  return this->doctype;
}
HtmlElement* Html::getElement()
{
  return this->element;
}
