#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>
#include <string>
#include "../errors/Error.h"

class FileReader{
 Error error;
public:
  FileReader();
  ~FileReader();
  std::string start(char*);
};

#endif
