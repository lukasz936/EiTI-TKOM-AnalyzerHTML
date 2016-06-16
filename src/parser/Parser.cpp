#include "Parser.h"

using namespace std;

//Productions:
//1. html ::= [doctype]  element
//2. doctype ::= Open_Doctype_Tag  [{text}]  [{value}]  Close_Tag
//3. element ::= start_tag   [ {element} ]   end_tag
//4. element ::= self_closing_tag
//5. element ::= [{text | value}]
//6. start_tag ::= open_start_tag   text   [ {attribute} ]   close_tag
//7. end_tag ::= open_end_tag   text   close_tag
//8. self_closing_tag ::= open_start_tag   tag_name [{attribute}] close_self_closing_tag
//9. attribute ::= text   equals_sign   value



Parser::Parser(Scanner* scanner)
{
  this->scanner=scanner;
  this->tokens=scanner->getPointerOnTokens();
}

Parser::~Parser()
{
  delete this->html;
}

//glowna funkcja parsera
void Parser::start()
{
  this->html = parseHtml();

}

//funkcja parsujaca obiekt typu Html (produkcja nr 1)
Html* Parser::parseHtml()
{
  Token* token;
  HtmlDoctype* doctype = NULL;
  HtmlElement* element = NULL;
  vector<string> texts;
  vector<string> values;
  if((token=scanner->nextSymbol())==NULL)
  return NULL;
  //mozliwa produkcja nr 2
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
      cout<<"Error in Parser. Unexpected token in Html. Expected: Close_Tag"<<endl;
      return NULL;
    }
  }
  //mozliwa produkcja nr 3
  if((element=parseElement())!=NULL)
  {
    return new Html(doctype,element);
  }
  else
  {
    cout<<"Error in Parser. Unexpected token in Html. Expected: Open_Start_Tag"<<endl;
    return NULL;
  }
  cout<<"Error in Parser. Unexpected token in Html. Expected: Open_Start_Tag"<<endl;
  return NULL;
}

//funkcja parsujaca obiekt typu HtmlElement
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
  //mozliwe produkcje: 3,4
  //mozliwa produkcja: 6
  if(token->getTokenType()==Open_Start_Tag)
  {
    token=scanner->nextSymbol();
    if(token!=NULL && token->getTokenType()==Text)
    {
      name=token->getContent();
      token=scanner->nextSymbol();
      while((attribute= parseAttribute())!=NULL)
      {
        attributes.push_back(attribute);
      }
      token = tokens->at(tokens->size()-1);
      //mozliwa produkcja: 4
      if(token!=NULL && token->getTokenType()==Close_Self_Closing_Tag)
      {
        scanner->nextSymbol();
        return new HtmlElement(name,attributes,"","",elements);
      }
      //mozliwa produkcja: 3
      else if(token!=NULL && token->getTokenType()==Close_Tag)
      {
        token=scanner->nextSymbol();
        while((element= parseElement())!=NULL)
        {
          elements.push_back(element);
        }
        token = tokens->at(tokens->size()-1);
        //mozliwa produkcja: 7
        if(token!=NULL && token->getTokenType()==Open_End_Tag)
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
          cout<<"Error in Parser. Unexpected token in HtmlElement. Expected: Open_Start_Tag"<<endl;
          return NULL;
        }
        cout<<"Error in Parser. Unexpected token in HtmlElement. Expected: Open_End_Tag"<<endl;
        return NULL;
      }
      cout<<"Error in Parser. Unexpected token in HtmlElement. Expected: Close_Tag"<<endl;
      return NULL;
    }
    cout<<"Error in Parser. Unexpected token in HtmlElement. Expected: Text"<<endl;
    return NULL;
  }
  //mozliwa produkcja nr 5
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

    if(text.at(text.size()-1)==' ')
    text.erase(text.end()-1,text.end());
    return new HtmlElement(name,attributes,text,"",elements);
  }
  return NULL;
}

//funkcja parsujaca obiekt typu HtmlAttribute (produkcja nr 9)
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
      else{
        cout<<"Error in Parser. Unexpected token in HtmlAttribute. Expected: Value"<<endl;
        return NULL;
      }
    }
    else{
      cout<<"Error in Parser. Unexpected token in HtmlAttribute. Expected: Equals_Sign"<<endl;
      return NULL;
    }
  }
  return NULL;
}

Html* Parser::getHtml()
{
  return this->html;
}

//funkcja wyszukujaca rekurencyjnie Element ( o podanych parametrach: nazwa elementu, opcjonalnie nazwa atrybutu i jego wartosc) zaczynajac poszukiwania od zadanego elementu startElement
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
