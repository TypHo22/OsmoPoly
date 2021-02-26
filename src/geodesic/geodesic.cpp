//geodesic
#include "geodesic.h"
#include "UTM.h"
////STL
#include <math.h>
//#define M_PI   3.14159265358979323846264338327950288
#define D_R (M_PI / 180.0)
#define R_D (180.0 / M_PI)
#define EarthRadiusX 6378137.0 //in meter

/*Coordinate-Bearing
*/
/*Destination point given distance and bearing from start point
Given a start point, initial bearing, and distance, this will calculate the destina­tion point
and final bearing travelling along a (shortest distance) great circle arc.
Formula from https://www.movable-type.co.uk/scripts/latlong.html
	Explanation of Bearing:
	//https://stackoverflow.com/questions/22668502/move-xy-coordinates-based-on-a-given-distance-and-bearing-from-transect
					0
					|
					|
					|
					|
	  270--------------------------   ------------------------------90
					|
					|
					|
					|
					|
				   180
*/

double geoBearing(node &startNode, node &endNode) // calculate bearing
{
    //const double lat1 = DegToRad(startNode.getGeo().lat);
    ////const double lon1 = DegToRad(startNode.getGeo().lon);
    //const double lat2 = DegToRad(endNode.getGeo().lat);
    ////const double lon2 = DegToRad(endNode.getGeo().lon);
    //const double deltaLon = DegToRad(endNode.getGeo().lon - startNode.getGeo().lon);
    //const double x = sin(deltaLon) * cos(lat2);
    //const double y = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(deltaLon);
    //const double bearingRAD = atan2(x,y);
    //double bearingDEG = fmod((RadToDeg(bearingRAD) + 360),360);
    //return bearingDEG;

    const double dL = endNode.getGeo().lon - startNode.getGeo().lon;
    const double X  = cos(endNode.getGeo().lon) * sin(dL);
    const double Y =  cos(startNode.getGeo().lat) * sin(endNode.getGeo().lat) - sin(startNode.getGeo().lon) * cos(endNode.getGeo().lat) * cos(dL);
    const double bearing = atan2(X,Y);
    return bearing;
}

node  geoDestination(node &startNode, double distance, double bearing)//distance in METER!
{
	bearing = DegToRad(bearing);
	const double lat1 = DegToRad(startNode.getGeo().lat);
	const double lon1 = DegToRad(startNode.getGeo().lon);
	const double d_R = distance / EarthRadiusX; //earth radius in km because FAKTOR1000
	double lat2 = asin(sin(lat1) * cos(d_R) + cos(lat1) * sin(d_R) * cos(bearing));
	double lon2 = lon1 + atan2(sin(bearing) * sin(d_R) * cos(lat1), cos(d_R) - sin(lat1) * sin(lat2));
	lat2 = RadToDeg(lat2); //calculate back to normal gps format
	lon2 = RadToDeg(lon2); //calculate back to normal gps format
	geo mGeoDest;
	mGeoDest.lon = lon2;
	mGeoDest.lat = lat2;
	mGeoDest.ele = 0.0;
	node destinationNode(mGeoDest);
	return destinationNode;
}

double geoDistance(node &startNode, node &endNode)//validiert
{
	const double lat1 = DegToRad(startNode.getGeo().lat);
	const double lon1 = DegToRad(startNode.getGeo().lon);
	const double lat2 = DegToRad(endNode.getGeo().lat);
	const double lon2 = DegToRad(endNode.getGeo().lon);

	const double deltaLat = lat2 - lat1;
	const double deltaLon = lon2 - lon1;

	const double a = sin(deltaLat / 2) * sin(deltaLat / 2) + cos(lat1) * cos(lat2) * sin(deltaLon / 2) * sin(deltaLon / 2);
	const double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	const double distance = EarthRadiusX * c;
	return distance; //distance in meter
}
