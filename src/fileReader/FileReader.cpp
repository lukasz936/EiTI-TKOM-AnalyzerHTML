#include "FileReader.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

FileReader::FileReader(){
}

FileReader::~FileReader(){
}

//glowna funkcja modulu obslugi wejscia zwracajaca obiektu typu string z zawartoscia pliku
string FileReader::start(char* fileDirectory){
  ifstream file;
  string inputSource = "";
  string tmp = "";

  file.open(fileDirectory);
  if (file)
  {
    while ( getline (file,tmp) )
    {
      inputSource+=tmp;
    }
    file.close();
    if(inputSource.size()==0)
    {
      cout<<"Error in File Reader. No sign in file."<<endl;
    }
  }
  else   cout<<"Error in File Reader. Cannot open file or file does not exist."<<endl;

  return inputSource;
}
