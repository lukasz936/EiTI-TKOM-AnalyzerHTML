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
      error.show(FILE_READER_EMPTY_FILE);
    }
  }
  else error.show(FILE_READER_UNABLE_TO_OPEN);

  return inputSource;
}
