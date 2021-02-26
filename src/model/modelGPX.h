#pragma once
///OsmoPoly
#include "model.h"
#include "../math/hull.h"
//STL
#include <memory>
#include <mutex>
class modelGPX : public model
{
public:
  modelGPX(std::string fileName);
  ~modelGPX();
  modelGPX(const modelGPX &source);
  modelGPX(modelGPX && source);
  modelGPX& operator=(const modelGPX& source);

  hull* getHull() const;
  void setHull(std::unique_ptr<hull> hull);

  void toExtractionFile();
private:
  std::string _fileName;
  std::unique_ptr<hull> _hull;
  std::mutex _mut;
};
