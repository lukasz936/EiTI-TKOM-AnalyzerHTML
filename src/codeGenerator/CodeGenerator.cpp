#include "CodeGenerator.h"
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

CodeGenerator::CodeGenerator()
{

}

CodeGenerator::~CodeGenerator()
{

}

//glowna funkcja generatora kodu
void CodeGenerator::start(Parser* parser, char* threatFilter, char* malwareFilter)
{
  this->parser=parser;
  HtmlElement* startElement = parser->getHtml()->getElement();
  string date;
  string threat;
  string malware;
  string host;
  string ipAddress;
  vector<HtmlElement*> objectJSON = parser->searchElements(startElement,"table","class","maintable");
  if(objectJSON.size()==0)
  {
    cout<<"Blad generacji kodu."<<endl;
    return;
  }
  objectJSON = parser->searchElements(objectJSON.at(0),"tr","","");
  if(objectJSON.size()==0)
  {
    cout<<"Blad generacji kodu."<<endl;
    return;
  }
  addFirstCharacters(); //dodanie poczatkowych znakow
for(int i=1;i<objectJSON.size();i++)  //glowna petla dodajaca obiekty
{
  threat=objectJSON.at(i)->getElements().at(1)->getElements().at(0)->getElements().at(0)->getText();
  malware=objectJSON.at(i)->getElements().at(2)->getElements().at(0)->getElements().at(0)->getText();
  if(checkFilter(threatFilter, malwareFilter, threat, malware))
  {
    date=objectJSON.at(i)->getElements().at(0)->getElements().at(0)->getText();
    host=objectJSON.at(i)->getElements().at(3)->getElements().at(1)->getElements().at(0)->getText();
    ipAddress=objectJSON.at(i)->getElements().at(5)->getElements().at(0)->getText();
    if(objectJSON.at(i)->getElements().at(5)->getElements().size()==3)
    ipAddress+=objectJSON.at(i)->getElements().at(5)->getElements().at(2)->getText();
    addObject(date,threat,malware,host,ipAddress);
  }
}
addLastCharachters(); //dodanie koncowych znakow
}

//funkcja dodajaca poczatkowe znaki
void CodeGenerator::addFirstCharacters()
{
  stringJSON="{\"Objects\":[";
}

//funkcja dodajaca pojedynczy obiekt
void CodeGenerator::addObject(string date, string thread, string malware, string host, string ipAddress)
{
  stringJSON+="{";
  stringJSON+="\"Date\": \""+date+"\",";
  stringJSON+="\"Threat\": \""+thread+"\",";
  stringJSON+="\"Malware\": \""+malware+"\",";
  stringJSON+="\"Host\": \""+host+"\",";
  stringJSON+="\"IP address (Country)\": \""+ipAddress+"\"";
  stringJSON+="},";
}

//funkcja dodajaca koncowe parametry
void CodeGenerator::addLastCharachters()
{
  if(stringJSON.at(stringJSON.size()-1)==',')
  stringJSON.erase(stringJSON.end()-1,stringJSON.end());
  stringJSON+="]}";
}

//funkcja sprawdzajaca czy wygeneraowac aktualny obiekt uwzgledniajac zastosowany filtr
bool CodeGenerator::checkFilter(char* threatFilter, char* malwareFilter,string threat, string malware)
{
  if(threatFilter==NULL && malwareFilter==NULL)
    return true;
  if(threatFilter!=NULL && malwareFilter==NULL)
  {
    if(threat.compare(threatFilter)==0)
      return true;
    else
      return false;
  }
  if(threatFilter==NULL && malwareFilter!=NULL)
  {
    if(malware.compare(malwareFilter)==0)
      return true;
    else
      return false;
  }
  if(threatFilter!=NULL && malwareFilter!=NULL)
  {
    if(threat.compare(threatFilter)==0 && malware.compare(malwareFilter)==0)
      return true;
    else
      return false;
  }
}

string CodeGenerator::getStringJSON()
{
  return this->stringJSON;
}
