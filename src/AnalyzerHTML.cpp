#include "AnalyzerHTML.h"

#include <string>
#include <vector>

using namespace std;
void display(vector<Token*>*);

AnalyzerHTML::AnalyzerHTML(int argc, char** argv){
  if(argc<2)
  {
    error.show(ANALYZER_WRONG_AGRUMENTS);
    return;
  }
  FileReader fileReader;
  FileCreator fileCreator;
  CodeGenerator codeGenerator;
  Scanner scanner(fileReader.start(argv[1]));
  Parser parser(&scanner);
  parser.start();
  codeGenerator.start(&parser);
  fileCreator.start(codeGenerator.getStringJSON());
  //while(scanner->nextSymbol()!=NULL);
  //display(scanner->getPointerOnTokens());
  //cout<<scanner->getPointerOnTokens()->size();


}

void display(vector<Token*>* tokens)
{
  for(int i=0;i<tokens->size();i++)
  {
    if(tokens->at(i)->getTokenType()==Open_Start_Tag)
    cout<<"1. Open_Start_Tag"<<endl;
    else if(tokens->at(i)->getTokenType()==Close_Tag)
    cout<<"2. Close_Tag"<<endl;
    else if(tokens->at(i)->getTokenType()==Open_End_Tag)
    cout<<"3. Open_End_Tag"<<endl;
    else if(tokens->at(i)->getTokenType()==Close_Self_Closing_Tag)
    cout<<"4. Close_Self_Closing_Tag"<<endl;
    else if(tokens->at(i)->getTokenType()==Equals_Sign)
    cout<<"5. Equals_Sign"<<endl;
    else if(tokens->at(i)->getTokenType()==Open_Doctype_Tag)
    cout<<"6. Open_Doctype_Tag"<<endl;
    else if(tokens->at(i)->getTokenType()==Open_Commment_Tag)
    cout<<"7. Open_Commment_Tag"<<endl;
    else if(tokens->at(i)->getTokenType()==Close_Comment_Tag)
    cout<<"8. Close_Comment_Tag"<<endl;
    else if(tokens->at(i)->getTokenType()==Value)
    cout<<"9. Value: " << tokens->at(i)->getContent()<<endl;
    else if(tokens->at(i)->getTokenType()==Text)
    cout<<"10. Text: " << tokens->at(i)->getContent()<<endl;

  }
}
