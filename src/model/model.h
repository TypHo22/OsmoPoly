#pragma once
///STL
#include <vector>
#include <memory>
#include <string>
///OsmoPoly
#include "node.h"

class model
{
public:
  model();
  ~model();
  model(const model &source);
  model(model && source);
  model& operator=(const model& source);
  model& operator=(const model&& source);
  void setNode(std::unique_ptr<node> mNode);

  std::vector<std::unique_ptr<node>>* getNodeHolder();
  void convertToXY();

private:
  std::vector<std::unique_ptr<node>> _nodeHolder;
  double _centralMeridian;
  std::string _fileName;
};
