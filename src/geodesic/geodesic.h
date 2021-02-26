#include "../model/node.h"
#include "UTM.h"
/*
    Useful Formulas for calculating with Geocoordinates
    All Formulas from: https://www.movable-type.co.uk/scripts/latlong.html
    I have cited the most formulas from the movable website because I could not explain it any better.
    "All these formulas are for calculations on the basis of a spherical earth (ignoring ellipsoidal effects)
    – which is accurate enough* for most purposes… [In fact, the earth is very slightly ellipsoidal; using
    a spherical model gives errors typically up to 0.3%" - Movable
    @Author: Andreas Bernatzky
    @Date: 28.09.19
*/


/*
"This uses the ‘haversine’ formula to calculate the great-circle distance between two points – that is, the shortest distance over the earth’s surface
– giving an ‘as-the-crow-flies’ distance between the points (ignoring any hills they fly over, of course!)." - Movable
*/
node geoDestination(node &startNode, double distance, double bearing);
/*
"In general, your current heading will vary as you follow a great circle path (orthodrome); the final heading will differ from the initial heading by varying degrees according
to distance and latitude (if you were to go from say 35°N,45°E ( Baghdad) to 35°N,135°E ( Osaka), you would start on a heading of 60° and end up on a heading of 120°!).
This formula is for the initial bearing (sometimes referred to as forward azimuth) which if followed in a straight line along a great-circle arc will take you from the start point to the end point" - Movable
*/
double geoBearing(node& startNode, node& endNode);
/*
"Given a start point, initial bearing, and distance, this will calculate the destina­tion point and final bearing travelling along a (shortest distance) great circle arc."- Movable
*/
double geoDistance(node& startNode, node& endNode);
