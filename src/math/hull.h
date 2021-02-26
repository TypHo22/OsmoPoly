#pragma once
///OsmoPoly
#include "../model/node.h"
#include "../geodesic/geodesic.h"
//STL
#include <vector>
#include <memory>
#include <mutex>
class hull
{

public:
  hull(double hullThickness);
  hull(const std::vector<std::unique_ptr<node>>* nodeHolder,double hullThickness);
  void calculateHull();
  void visualize();

  std::vector<std::unique_ptr<node>>* getHull();

private:
  //Member
  double _hullThickness;
  const std::vector<std::unique_ptr<node>>* p_nodeHolder;
  std::vector<std::unique_ptr<node>> _hull;
  std::mutex _mut;
};

