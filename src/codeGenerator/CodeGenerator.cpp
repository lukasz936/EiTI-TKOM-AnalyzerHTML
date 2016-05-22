#include "CodeGenerator.h"

using namespace std;
CodeGenerator::CodeGenerator()
{

}

CodeGenerator::~CodeGenerator()
{

}

string CodeGenerator::getStringJSON()
{
  return this->stringJSON;
}

void CodeGenerator::start(Parser* parser)
{
  this->parser=parser;
  HtmlElement* startElement = parser->getHtml()->getElement();
  string date;
  string threat;
  string malware;
  string host;
  string ipAddress;
  vector<HtmlElement*> objectJSON = parser->searchElements(startElement,"table","class","maintable");
  objectJSON = parser->searchElements(objectJSON.at(0),"tr","","");

  addFirstCharacters();
  for(int i=1;i<objectJSON.size();i++)
  {
    date=objectJSON.at(i)->getElements().at(0)->getElements().at(0)->getText();
    threat=objectJSON.at(i)->getElements().at(1)->getElements().at(0)->getElements().at(0)->getText();
    malware=objectJSON.at(i)->getElements().at(2)->getElements().at(0)->getElements().at(0)->getText();
    host=objectJSON.at(i)->getElements().at(3)->getElements().at(1)->getElements().at(0)->getText();
    ipAddress=objectJSON.at(i)->getElements().at(5)->getElements().at(0)->getText();
    if(objectJSON.at(i)->getElements().at(5)->getElements().size()==3)
      ipAddress+=objectJSON.at(i)->getElements().at(5)->getElements().at(2)->getText();
    addObject(date,threat,malware,host,ipAddress);
  }
  addLastCharachters();

}

void CodeGenerator::addFirstCharacters()
{
  stringJSON="{\"Objects\":[";
}

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
void CodeGenerator::addLastCharachters()
{
  if(stringJSON.at(stringJSON.size()-1)==',')
  stringJSON.erase(stringJSON.end()-1,stringJSON.end());
  stringJSON+="]}";
}
