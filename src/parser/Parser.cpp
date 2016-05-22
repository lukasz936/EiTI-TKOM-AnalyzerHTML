#include "Parser.h"

using namespace std;

Parser::Parser(Scanner* scanner)
{
  this->scanner=scanner;
  this->tokens=scanner->getPointerOnTokens();
}

Parser::~Parser()
{
  delete this->html;
}

void Parser::start()
{
  this->html = parseHtml();

}

Html* Parser::parseHtml()
{
  Token* token;
  HtmlDoctype* doctype = NULL;
  HtmlElement* element = NULL;
  vector<string> texts;
  vector<string> values;
  if((token=scanner->nextSymbol())==NULL)
  return NULL;
  if(token->getTokenType()==Open_Doctype_Tag)
  {
    token=scanner->nextSymbol();
    if(token!=NULL && token->getTokenType()==Text)
    {
      texts.push_back(token->getContent());
      while((token=scanner->nextSymbol()) && token->getTokenType()==Text)
      {
        texts.push_back(token->getContent());
      }
    }
    if(token!=NULL && token->getTokenType()==Value)
    {
      values.push_back(token->getContent());
      while((token=scanner->nextSymbol()) && token->getTokenType()==Value)
      {
        values.push_back(token->getContent());
      }
    }
    if(token!=NULL && token->getTokenType()==Close_Tag)
    {
      doctype = new HtmlDoctype(texts, values);
      token=scanner->nextSymbol();
    }
    else
    {
      error.show(PARSER_INVALID_TOKEN_HTML);
      return NULL;
    }
  }
  if((element=parseElement())!=NULL)
  {
    return new Html(doctype,element);
  }
  else
  {
    error.show(PARSER_INVALID_TOKEN_HTML);
    return NULL;
  }
  error.show(PARSER_INVALID_TOKEN_HTML);
  return NULL;
}

HtmlElement* Parser::parseElement()
{
  Token* token = tokens->at(tokens->size()-1);
  HtmlElement* element = NULL;
  string text="";
  string name="";
  vector<HtmlAttribute*> attributes;
  vector<HtmlElement*> elements;
  HtmlAttribute* attribute;
  if(token==NULL)
  return NULL;
  if(token->getTokenType()==Open_Start_Tag)
  {
    token=scanner->nextSymbol();
    if(token!=NULL && token->getTokenType()==Text)//start_tag lub self_closing_tag
    {
      name=token->getContent();
      token=scanner->nextSymbol();
      while((attribute= parseAttribute())!=NULL)
      {
        attributes.push_back(attribute);
      }
      token = tokens->at(tokens->size()-1);
      if(token!=NULL && token->getTokenType()==Close_Self_Closing_Tag)
      {
        scanner->nextSymbol();
        return new HtmlElement(name,attributes,"","",elements);
      }
      else if(token!=NULL && token->getTokenType()==Close_Tag)  //koniec start_tag.
      {
        token=scanner->nextSymbol();
        while((element= parseElement())!=NULL)
        {
          elements.push_back(element);
        }
        token = tokens->at(tokens->size()-1);
        if(token!=NULL && token->getTokenType()==Open_End_Tag)  //end tag
        {
          token=scanner->nextSymbol();
          if(token==NULL || token->getTokenType()!=Text)
          return NULL;
          token=scanner->nextSymbol();
          if(token!=NULL && token->getTokenType()==Close_Tag)
          {
            scanner->nextSymbol();
            return new HtmlElement(name,attributes,text,"",elements);
          }
        }
        else
        return NULL;
      }
    }
  }
  else if(token->getTokenType()==Text || token->getTokenType()==Value)
  {
    if(token->getTokenType()==Value)
        text+=("\"" + token->getContent() + "\" ");
      else
        text+=(token->getContent()+" ");
    while((token=scanner->nextSymbol()) && (token->getTokenType()==Text || token->getTokenType()==Value))
    {
    if(token->getTokenType()==Value)
        text+=("\"" + token->getContent() + "\" ");
      else
        text+=(token->getContent()+" ");
    }
  //  std::cout<<text<<endl;
    return new HtmlElement(name,attributes,text,"",elements);
  }

  return NULL;
}

HtmlAttribute* Parser::parseAttribute()
{
  Token* token = tokens->at(tokens->size()-1);
  string name;
  string value;
  if(token==NULL)
  return NULL;
  if(token->getTokenType()==Text)
  {
    name=token->getContent();
    token=scanner->nextSymbol();
    if(token!=NULL && token->getTokenType()==Equals_Sign)
    {
      token=scanner->nextSymbol();
      if(token!=NULL && token->getTokenType()==Value)
      {
        value=token->getContent();
        scanner->nextSymbol();
        return new HtmlAttribute(name,value);
      }
    }
  }
  return NULL;
}

Html* Parser::getHtml()
{
  return this->html;
}

vector<HtmlElement*> Parser::searchElements(HtmlElement* startElement, string name, string attributeName, string attributeValue)
{
  vector<HtmlElement*> htmlElements;
  vector<HtmlElement*> tmpElements;
  HtmlElement* tmpElement;
  for(int i=0;i<startElement->getElements().size();i++)
  {
    tmpElement=startElement->getElements().at(i);
    if(tmpElement->getName()==name)
    {
      if(attributeName!="" && attributeValue!="")
      {
        for(int j=0;j<tmpElement->getAttributes().size();j++)
        {
          if(tmpElement->getAttributes().at(j)->getName()==attributeName && tmpElement->getAttributes().at(j)->getValue()==attributeValue)
          htmlElements.push_back(startElement->getElements().at(i));
        }
      }
      else
      htmlElements.push_back(startElement->getElements().at(i));
    }
  }
  for(int i=0;i<startElement->getElements().size();i++)
  {
    tmpElements=searchElements(startElement->getElements().at(i),name,attributeName,attributeValue);
      for(int j=0;j<tmpElements.size();j++)
      {
          htmlElements.push_back(tmpElements.at(j));
      }
  }
  return htmlElements;
}

void Parser::displaySymbol(Token* token)
{
  if(token->getTokenType()==Open_Start_Tag)
  cout<<"1. Open_Start_Tag"<<endl;
  else if(token->getTokenType()==Close_Tag)
  cout<<"2. Close_Tag"<<endl;
  else if(token->getTokenType()==Open_End_Tag)
  cout<<"3. Open_End_Tag"<<endl;
  else if(token->getTokenType()==Close_Self_Closing_Tag)
  cout<<"4. Close_Self_Closing_Tag"<<endl;
  else if(token->getTokenType()==Equals_Sign)
  cout<<"5. Equals_Sign"<<endl;
  else if(token->getTokenType()==Open_Doctype_Tag)
  cout<<"6. Open_Doctype_Tag"<<endl;
  else if(token->getTokenType()==Open_Commment_Tag)
  cout<<"7. Open_Commment_Tag"<<endl;
  else if(token->getTokenType()==Close_Comment_Tag)
  cout<<"8. Close_Comment_Tag"<<endl;
  else if(token->getTokenType()==Value)
  cout<<"9. Value: " << token->getContent()<<endl;
  else if(token->getTokenType()==Text)
  cout<<"10. Text: " << token->getContent()<<endl;
}
