#pragma once
#include "model.h"
class modelOSM : public model
{
public:
  modelOSM();
  ~modelOSM();
  modelOSM(const modelOSM &source);
  modelOSM(modelOSM && source);
  modelOSM& operator=(const modelOSM& source);
private:

};
