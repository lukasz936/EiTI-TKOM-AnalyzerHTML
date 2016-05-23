#include "CodeGenerator.h"

using namespace std;
CodeGenerator::CodeGenerator()
{

}

CodeGenerator::~CodeGenerator()
{

}

//glowna funkcja generatora kodu
void CodeGenerator::start(Parser* parser, char* filter)
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
  setCodeGeneratorType(filter); //ustawienie typu generatora kodu uwzgledniajac zastowany filtr lub jego brak
  addFirstCharacters(); //dodanie poczatkowych znakow
  for(int i=1;i<objectJSON.size();i++)  //glowna petla dodajaca obiekty
  {
    threat=objectJSON.at(i)->getElements().at(1)->getElements().at(0)->getElements().at(0)->getText();
    malware=objectJSON.at(i)->getElements().at(2)->getElements().at(0)->getElements().at(0)->getText();
    if(checkFilter(threat, malware))
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

//punkcja ustawiajaca typ generatora kodu uwzgledniacajac zastosowany filter lub jego brak
void CodeGenerator::setCodeGeneratorType(char* filter)
{
  if(filter==NULL)
  {
    this->codeGeneratorType=None_Filter;
  }
  else
  {
    string stringFilter(filter);
    if(stringFilter=="")
    this->codeGeneratorType=None_Filter;
    else if(stringFilter=="TeslaCrypt")
    this->codeGeneratorType=Malware_Filter_TeslaCrypt;
    else if(stringFilter=="CryptoWall")
    this->codeGeneratorType=Malware_Filter_CryptoWall;
    else if(stringFilter=="TorrentLocker")
    this->codeGeneratorType=Malware_Filter_TorrentLocker;
    else if(stringFilter=="PadCrypt")
    this->codeGeneratorType=Malware_Filter_PadCrypt;
    else if(stringFilter=="Locky")
    this->codeGeneratorType=Malware_Filter_Locky;
    else if(stringFilter=="CTB-Locker")
    this->codeGeneratorType=Malware_Filter_CTB_Locker;
    else if(stringFilter=="FAKBEN" || stringFilter=="Fakben")
    this->codeGeneratorType=Malware_Filter_Fakben;
    else if(stringFilter=="PayCrypt")
    this->codeGeneratorType=Malware_Filter_PadCrypt;
    else if(stringFilter=="Botnet")
    this->codeGeneratorType=Threat_Filter_Botnet;
    else if(stringFilter=="PaymentSites")
    this->codeGeneratorType=Threat_Filter_PaymentSites;
    else if(stringFilter=="DistributionSites")
    this->codeGeneratorType=Threat_Filter_DistributionSites;
    else
    this->codeGeneratorType=Wrong_Filter;
  }
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
bool CodeGenerator::checkFilter(string threat, string malware)
{

  if(this->codeGeneratorType==None_Filter)
  return true;
  else if(codeGeneratorType==Malware_Filter_TeslaCrypt)
  {
    if(malware=="TeslaCrypt")
      return true;
  }
  else if(codeGeneratorType==Malware_Filter_CryptoWall)
  {
    if(malware=="CryptoWall")
      return true;
  }
  else if(codeGeneratorType==Malware_Filter_TorrentLocker)
  {
    if(malware=="TorrentLocker")
      return true;
  }
  else if(codeGeneratorType==Malware_Filter_PadCrypt)
  {
    if(malware=="PadCrypt")
      return true;
  }
  else if(codeGeneratorType==Malware_Filter_Locky)
  {
    if(malware=="Locky")
      return true;
  }
  else if(codeGeneratorType==Malware_Filter_CTB_Locker)
  {
    if(malware=="CTB-Locker")
      return true;
  }
  else if(codeGeneratorType==Malware_Filter_Fakben)
  {
    if(malware=="FAKBEN")
      return true;
  }
  else if(codeGeneratorType==Malware_Filter_PadCrypt)
  {
    if(malware=="PadCrypt")
      return true;
  }
  else if(codeGeneratorType==Threat_Filter_Botnet)
  {
    if(threat=="Botnet C&amp;C")
      return true;
  }
  else if(codeGeneratorType==Threat_Filter_PaymentSites)
  {
    if(threat=="Payment Site")
      return true;
  }
  else if(codeGeneratorType==Threat_Filter_DistributionSites)
  {
    if(threat=="Distribution Site")
      return true;
  }
  else if(codeGeneratorType==Wrong_Filter)
    return false;
}

string CodeGenerator::getStringJSON()
{
  return this->stringJSON;
}
