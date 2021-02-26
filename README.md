# OsmoPoly

Osmosis is a command line application for processing data from open streetmaps. Osmosis offers the
possibility to extract data from a .osm file with a polygon. A detailed usage of Osmosis can be found
here https://wiki.openstreetmap.org/wiki/Osmosis
Often it is needed to extract a specific area really big .osm-files like they can be found on
https://download.geofabrik.de/index.html
The program „OsmoPoly“ offers the possibility to calculate the geocoordinates of a polygon
around a given route. The route is specified by a .gpx-File from www.graphhopper.com

Further details in the pdf

Build on Linux:
sudo apt-get install gnuplot gnuplot 

In OsmoPoly Folder:
mkdir build
cd build 
cmake ..
make 

Build on Windows:
not tested
