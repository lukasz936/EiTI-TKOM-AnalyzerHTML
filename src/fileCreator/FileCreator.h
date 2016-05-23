#ifndef FILE_CREATOR_H
#define FILE_CREATOR_H


#include "../errors/Error.h"
#include <iostream>

class FileCreator{
public:
  FileCreator();
  ~FileCreator();
  void start(std::string);
};

#endif
