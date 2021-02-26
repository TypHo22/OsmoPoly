#include "model.h"
#include"../geodesic/UTM.h"
///STL
#include<algorithm>


model::model()
{

}

model::~model()
{
  for(auto&a : _nodeHolder)
  {
    a.release();
  }
}

model::model(const model& source) //Copy Constructor
{
  _nodeHolder.reserve(source._nodeHolder.size());
  for(const auto& a : source._nodeHolder)
  {
    _nodeHolder.push_back(std::make_unique<node>(*a));
  }

  _centralMeridian = source._centralMeridian;
  _fileName = source._fileName;
}

model::model(model&& source)//Move Constructor
{
  _nodeHolder = std::move(source._nodeHolder);
  _centralMeridian = source._centralMeridian;
  _fileName = source._fileName;
}

model &model::operator=(const model& source) //Copy Assign
{
  if(this == &source)
    return *this;

  for(const auto& a : source._nodeHolder)
  {
    _nodeHolder.push_back(std::make_unique<node>(*a));
  }

  _centralMeridian = source._centralMeridian;
  _fileName = source._fileName;

  return* this;
}

void model::setNode(std::unique_ptr<node> mNode)
{
  _nodeHolder.push_back(std::move(mNode));
}

std::vector<std::unique_ptr<node>>* model::getNodeHolder()
{
  return &_nodeHolder;
}

void model::convertToXY()
{
    double lonMax = _nodeHolder.begin()->get()->getGeo().lon;
    double lonMin = _nodeHolder.begin()->get()->getGeo().lon;

    for(const auto &lonP : _nodeHolder)
    {
      if(lonP.get()->getGeo().lon < lonMin)
        lonMin = lonP.get()->getGeo().lon;

      if(lonP.get()->getGeo().lon > lonMax)
        lonMax = lonP.get()->getGeo().lon;
    }

    _centralMeridian = lonMin + (lonMax - lonMin);

    for(const auto &mNode : _nodeHolder)
    {
      float x,y;
      geo mGeo = mNode.get()->getGeo();
      LatLonToUTMXY(DegToRad(mGeo.lat),DegToRad(mGeo.lon),0,x,y);
      mNode.get()->setBase(base(x,y,mGeo.ele));
    }
}
