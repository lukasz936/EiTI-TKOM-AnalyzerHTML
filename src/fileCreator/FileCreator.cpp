#include "FileCreator.h"
#include <iostream>
#include <fstream>

using namespace std;
FileCreator::FileCreator()
{

}

FileCreator::~FileCreator()
{

}

//glowna funkcja modulu obslugi wyjscia zapisujaca plik w formacie JSON
void FileCreator::start(string stringJSON)
{
    ofstream ofs;
    ofs.open ("output.json",ofstream::binary);

    ofs <<stringJSON;

    ofs.close();

}
