#include "AnalyzerHTML.h"

#include <string>
#include <vector>
#include <string.h>

using namespace std;
void display(vector<Token*>*);

//glowna funkcja przeprowadzajace analize pliku html
AnalyzerHTML::AnalyzerHTML(int argc, char** argv){
  if(argc<2 || argc ==3 ||argc ==5 ||argc>6)
  {
    cout<<"Error. Cannot to start a program. Invalid number of input arguments."<<endl;
    return;
  }
  FileReader fileReader;
  FileCreator fileCreator;
  CodeGenerator codeGenerator;
  Scanner scanner(fileReader.start(argv[1]));
  Parser parser(&scanner);
  parser.start();
  startGenerateCode(argc, argv, &parser, &codeGenerator);
  fileCreator.start(codeGenerator.getStringJSON());
}

void AnalyzerHTML::startGenerateCode(int argc, char** argv, Parser* parser, CodeGenerator* codeGenerator)
{
  if(argc==2)
    codeGenerator->start(parser,NULL,NULL);
  else if(argc==4)
  {
    if(strcmp(argv[2],"-threat")==0)
      codeGenerator->start(parser,argv[3],NULL);
    else if(strcmp(argv[2],"-malware")==0)
      codeGenerator->start(parser,NULL,argv[3]);
    else
      cout<<"Error. Cannot to start a program. Invalid type of input arguments."<<endl;
  }
  else
  {
    if(strcmp(argv[2],"-threat")==0 && strcmp(argv[4],"-malware")==0)
      codeGenerator->start(parser,argv[3],argv[5]);
    else if(strcmp(argv[2],"-malware")==0 && strcmp(argv[4],"-threat")==0)
      codeGenerator->start(parser,argv[5],argv[3]);
    else
      cout<<"Error. Cannot to start a program. Invalid type of input arguments."<<endl;
  }
}
