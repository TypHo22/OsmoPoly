## OsmoPoly

**Introduction**

_Osmosis_ is a command line application for processing data from open streetmaps. 
_Osmosis_ offers the possibility to extract data from a .osm file with a so called extraction polygon.

A detailed usage of Osmosis can be found here:<br/>
`https://wiki.openstreetmap.org/wiki/Osmosis`

A explanation for the extraction polygons can be found here:<br/>
`https://wiki.openstreetmap.org/wiki/Osmosis/Polygon_Filter_File_Format`

Often it is needed to extract a specific area of a really big .osm-files like they can be found on<br/>
`https://download.geofabrik.de/index.html`<br/>
The program _OsmoPoly_ offers the possibility to calculate the geocoordinates of such an extraction polygon
around a given route which can be used in _Osmosis_. 
The route is specified by a .gpx-File from<br/>
`www.graphhopper.com`

**Usage Example**

We want to calculate an extraction polygon around the route from Hamburg, Germany to Hannover, Germany.
![image](https://user-images.githubusercontent.com/42981587/109389296-49396a00-790c-11eb-8846-fb2da954f00d.png)

_Step 1:_</br>
Download the .gpx from `www.graphhopper.com` </br>

![image](https://user-images.githubusercontent.com/42981587/109389359-7be36280-790c-11eb-85ca-186c8ce202fb.png)

![image](https://user-images.githubusercontent.com/42981587/109389366-800f8000-790c-11eb-9fb0-bd09183027a9.png)

_Step 2:_</br>
Execute OsmoPoly in build directory </br>
Specify as first input parameter _path to file_ and next the _size of the extraction polgon in meter_
_./OsmoPoly /home/andreas/Documents/OsmoPoly/test/dat1.gpx 1500 /home/andreas/Documents/OsmoPoly/test/dat2.gpx 1500 

You can convert so many .gpx files to polygon files as you want. Just make sure you always have the following order: </br>
_"path to file" "extraction size" "path to file" "extraction size"_

OsmoPoly will always show the result in two plots per conversino. One UTM plot and one Geodesic plot: </br>
![image](https://user-images.githubusercontent.com/42981587/109389772-23ad6000-790e-11eb-86cc-9461dfc155a0.png)


The extracted files can be found as .txt files in build folder. To use it with Osmosis do not forget to change the file ending
to .poly. </br>


_Math behind it_ </br>
The pink line with its waypoints A,B,C,D,E represent our .gpx-route. The red points represent the extraction hull. </br>
The hullpoints are calculated perpendicular to the blue route points and their heading to the next point. </br>
The distance between a routepoint (blue) and a hullpoint  (red) is specified by the entered _extraction size_ in meter. </br>
The calculation of the hullpoint coordinates is done by geodesic algorithms. 

![image](https://user-images.githubusercontent.com/42981587/109389778-2d36c800-790e-11eb-9613-c41772c310d2.png)

**build** </br>
The current plotting library SciPlot uses the interface of gnuplot.</br> So first install gnuPlot.</br>
_Linux:_ </br>
`sudo apt-get install gnuplot`</br>
In OsmoPolyfolder:</br>
`mkdir build` </br>
`cd build` </br>
`cmake .. `</br>
`make`</br>

_Windows:_ </br>
Haven not figured out how to access interface SciPlot Interface on Windows. </br>
Probably will switch the plotting library fot it to MatPlot-Lib </br>
But the code also builds on Windows. Just remove all the plotting stuff in </br>
_hull.cpp_ in method 'hull::visualize'

**Issues**</br>
Creating Extraction Polygons from OpenStreetmap files is not supported yet.</br>
I noticed I need to provide a proper UI for that. It is highly possible that I will switch </br>
to Qt for creating a reasonable UI and do all the visualization with Qt to ensure that it also </br>
builds on windows
Don't know, maybe I switch on Qt for that.

**License**</br>
Feel free to use it. 


