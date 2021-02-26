#pragma once

struct base
{
  double x;
  double y;
  double z;

  base():x(0),y(0),z(0){}

  base(double x, double y, double z)
    :x(x),y(y),z(z){}

  base(double x, double y)
    :x(x),y(y){}
};

struct geo
{
  double lat;
  double lon;
  double ele;

  geo():lat(0),lon(0),ele(0){}

  geo(double lat, double lon, double ele)
    :lat(lat),lon(lon),ele(ele){}

  geo(double lat, double lon)
    :lat(lat),lon(lon){}
};

class node
{
public:
  node();
  node(node&& source);
  node(node& source);
  node(base base);
  node(geo  geo);
  node(double lat, double lon, double ele);
  node(double lat, double lon);
  ~node();

  base* getpBase();
  base getBase() const;
  void setBase(const base &mbase);


  geo getGeo() const;
  void setGeo(const geo &geo);

  //methods
  double calcHeading(node anotherNode);
  double calcBearing(node anotherNode);
  node calcLeftPerpendicular(double currentBearing, const double distance);
  node calcRightPerpendicular(double currentBearing, const double distance);

private:
  base _base;
  geo  _geo;
};
