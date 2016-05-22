#include "Error.h"
#include <iostream>

using namespace std;

Error::Error(){
}

Error::~Error(){
}

void Error::show(ErrorType errorType)
{
  switch(errorType)
  {
    case ANALYZER_WRONG_AGRUMENTS:
    cout<<"Blad wywolania programu. Nieprawidowa liczba argumentow wejsciowych."<<endl;
    break;
    case FILE_READER_UNABLE_TO_OPEN:
    cout<<"Blad odczytu pliku. Nie mozna otworzyc pliku lub podana sciezka nie istnieje."<<endl;
    break;
    case FILE_READER_EMPTY_FILE:
    cout<<"Blad odczytu pliku. Zadany plik nie zawiera znakow do analizy."<<endl;
    break;
    case SCANNER_INVALID_SIGN:
    cout<<"Blad analizy leksykalnej. Niewlasciwy znak."<<endl;
    break;
    case PARSER_INVALID_TOKEN_HTML:
    cout<<"Blad analizy skladniowej. Niewlasciwy atom leksykalny podczas parsowania obiektu typu Html."<<endl;
    break;
    case PARSER_INVALID_TOKEN_ELEMENT:
    cout<<"Blad analizy skladniowej. Niewlasciwy atom leksykalny podczas parsowania obiektu typu Element."<<endl;
    break;
  }
}
