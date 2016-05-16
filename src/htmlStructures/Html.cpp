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
