#ifndef ERROR_H
#define ERROR_H
#include "ErrorType.h"


class Error{
  public:
    Error();
    ~Error();
    void show(ErrorType errorType);
};
#endif
