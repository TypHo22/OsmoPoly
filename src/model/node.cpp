#include "node.h"
#include "../geodesic/UTM.h"
#include "../geodesic/geodesic.h"
node::node()
{

}

node::node(node &&source)
{
  _geo = source._geo;
  _base = source._base;
}

node::node(node &source)
{
  _geo = source._geo;
  _base = source._base;
}

node::~node()
{

}

base* node::getpBase()
{
 return &_base;
}

node::node(base base)
{
  _base = base;
}

node::node(geo geo)
{
  _geo = geo;
}

node::node(double lat, double lon, double ele)
{
  geo mGeo(lat,lon,ele);
  _geo = mGeo;
}

node::node(double lat, double lon)
{
  geo mGeo(lat,lon);
  _geo = mGeo;
}

base node::getBase() const
{
  return _base;
}

void node::setBase(const base &mbase)
{
  _base = mbase;
}

geo node::getGeo() const
{
  return _geo;
}

void node::setGeo(const geo &geo)
{
  _geo = geo;
}

double node::calcHeading(node anotherNode)
{
  const double dX = anotherNode.getBase().x - this->getBase().x;
  const double dY = anotherNode.getBase().y - this->getBase().y;
  return atan2(dY,dX);
}

double node::calcBearing(node anotherNode)
{
  return geoBearing(*this,anotherNode);
}

node node::calcLeftPerpendicular( double currentBearing, const double distance)
{
 // currentBearing = RadToDeg(currentBearing);
  double resBearing = currentBearing - 90;

  if(resBearing < 0)
    resBearing = 360 + resBearing;

  return geoDestination(*this,distance, resBearing);
}

node node::calcRightPerpendicular(double currentBearing, const double distance)
{
  //currentBearing = RadToDeg(currentBearing);
  double resBearing = currentBearing + 90;

  if(resBearing > 360)
    resBearing =- 360;

  return geoDestination(*this,distance, resBearing);
}

