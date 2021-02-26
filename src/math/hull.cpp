///OsmoPoly
#include "hull.h"
#include "../geodesic/geodesic.h"
///thrid party
#include <sciplot/sciplot.hpp>
///STL
#include <algorithm>    // std::reverse

hull::hull(double hullThickness): _hullThickness(hullThickness) {}


hull::hull(const std::vector<std::unique_ptr<node> > *nodeHolder, double hullThickness) :
  p_nodeHolder(nodeHolder),_hullThickness(hullThickness)
{

}

void hull::calculateHull()
{
  _mut.lock();
  //calculate hull in two loops to have it already sorted for plotting
  for(size_t a = 0; a < p_nodeHolder->size();a++)
  {
      if(a == p_nodeHolder->size()-1)
      {
        const double lastBearing = p_nodeHolder->end()[-2].get()->calcBearing(*p_nodeHolder->back().get());

        node left = p_nodeHolder->back()->calcLeftPerpendicular(lastBearing,_hullThickness);

        //convert new geoNodes to xy
        float x,y;
        geo lGeo = left.getGeo();

        LatLonToUTMXY(DegToRad(lGeo.lat),DegToRad(lGeo.lon),0,x,y);
        left.setBase((base(x,y,lGeo.ele)));
        _hull.emplace_back(std::unique_ptr<node>(new node(std::move(left))));
        break;
      }

      //bearing between node[a] and succeding node
      const double currentBearing = p_nodeHolder->at(a).get()->calcBearing(*p_nodeHolder->at(a + 1).get());
      //perpendicular left to currentBearing
      node left = p_nodeHolder->at(a).get()->calcLeftPerpendicular(currentBearing,_hullThickness);

      //convert new geoNodes to xy
      float x,y;
      geo lGeo = left.getGeo();

      LatLonToUTMXY(DegToRad(lGeo.lat),DegToRad(lGeo.lon),0,x,y);
      left.setBase((base(x,y,lGeo.ele)));


      _hull.emplace_back(std::unique_ptr<node>(new node(std::move(left))));
    }
  std::reverse(_hull.begin(),_hull.end());
  for(size_t a = 0; a < p_nodeHolder->size();a++)
  {
      if(a == p_nodeHolder->size()-1)
      {
        const double lastBearing = p_nodeHolder->end()[-2].get()->calcBearing(*p_nodeHolder->back().get());

        node right = p_nodeHolder->back()->calcRightPerpendicular(lastBearing,_hullThickness);

        //convert new geoNodes to xy
        float x,y;
        geo rGeo = right.getGeo();

        LatLonToUTMXY(DegToRad(rGeo.lat),DegToRad(rGeo.lon),0,x,y);
        right.setBase((base(x,y,rGeo.ele)));
        _hull.emplace_back(std::unique_ptr<node>(new node(std::move(right))));
        break;
      }

      //bearing between node[a] and succeding node
      const double currentBearing = p_nodeHolder->at(a).get()->calcBearing(*p_nodeHolder->at(a + 1).get());
      //perpendicular left to currentBearing
      node right = p_nodeHolder->at(a).get()->calcRightPerpendicular(currentBearing,_hullThickness);

      //convert new geoNodes to xy
      float x,y;
      geo rGeo = right.getGeo();

      LatLonToUTMXY(DegToRad(rGeo.lat),DegToRad(rGeo.lon),0,x,y);
      right.setBase((base(x,y,rGeo.ele)));

      _hull.emplace_back(std::unique_ptr<node>(new node(std::move(right))));
    }

    _hull.emplace_back(std::unique_ptr<node>(new node(*_hull.begin()->get())));
    _mut.unlock();
}

void hull::visualize()
{
  _mut.lock();
  using namespace sciplot;

  std::vector<double> xHull(_hull.size());
  std::vector<double> yHull(_hull.size());
  for(size_t xyH = 0; xyH < _hull.size();xyH++)
  {
      xHull[xyH] = _hull.at(xyH).get()->getBase().x;
      yHull[xyH] = _hull.at(xyH).get()->getBase().y;
  }

  std::vector<double> xPath(p_nodeHolder->size());
  std::vector<double> yPath(p_nodeHolder->size());
  for(size_t xyP = 0; xyP < p_nodeHolder->size();xyP++)
  {
      xPath[xyP] = p_nodeHolder->at(xyP).get()->getBase().x;
      yPath[xyP] = p_nodeHolder->at(xyP).get()->getBase().y;
  }

  std::vector<double> geoxHull(_hull.size());
  std::vector<double> geoyHull(_hull.size());
  for(size_t geoH = 0; geoH < _hull.size();geoH++)
  {
      geoxHull[geoH] = _hull.at(geoH).get()->getGeo().lon;
      geoyHull[geoH] = _hull.at(geoH).get()->getGeo().lat;
  }

  std::vector<double> geoxPath(p_nodeHolder->size());
  std::vector<double> geoyPath(p_nodeHolder->size());
  for(size_t geoP = 0; geoP < p_nodeHolder->size();geoP++)
  {
      geoxPath[geoP] = p_nodeHolder->at(geoP).get()->getGeo().lon;
      geoyPath[geoP] = p_nodeHolder->at(geoP).get()->getGeo().lat;
  }

  //create plots
  //geoPlot
  sciplot::plot geoPlot;
  geoPlot.draw(geoxPath,geoyPath).title("path");
  geoPlot.draw(geoxHull,geoyHull).title("hull");
  geoPlot.xlabel("longitute");
  geoPlot.ylabel("latitude");
  geoPlot.show();
  //xyPlot
  sciplot::plot xyPlot;
  xyPlot.draw(xPath,yPath).title("path");
  xyPlot.draw(xHull,yHull).title("hhull");
  xyPlot.xlabel("x");
  xyPlot.ylabel("y");
  xyPlot.show();
  _mut.unlock();
}

std::vector<std::unique_ptr<node> > *hull::getHull()
{
  return &_hull;
}




