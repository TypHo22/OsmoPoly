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


**REVIEWER**
The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed.

To get this rubric reviewed, Update the Readme file with the mention of at least 5 places(of below mentioned sections) where rubric points were met requirements:raised_hands:

Loops, Functions, I/O
Object Oriented Programming
Memory Management
Concurrency
Compiling and Testing (All Rubric Points REQUIRED)
The project code must compile and run without errors.

We strongly recommend using cmake and make, as provided in the starter repos. If you choose another build system, the code must compile on any reviewer platform.

Fantastic job, The project compiles perfectly, the project is working perfectly and I loved it :wink:

Loops, Functions, I/O
**main.cpp,hull.cpp,model.cpp,modelGPX.cpp**

The project code is clearly organized into functions.
**geodesic.cpp,UTM.cpp**

The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
**main.cpp**

The project accepts input from a user as part of the necessary operation of the program.
**modelGPX::toExtractionFile()**

Object Oriented Programming
**model.h,modelGPX.h,node.h,hull.h,fileHandler.h***

All class data members are explicitly specified as public, protected, or private.
**model.h,modelGPX.h,node.h,hull.h,fileHandler.h***


All class members that are set to argument values are initialized through member initialization lists.
**model.h,modelGPX.h,node.h,hull.h,fileHandler.h***

All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
**Project is structured in folders for that. model,geodesic,math and so on...**

Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.
**model.h,modelGPX.h,node.h,hull.h,fileHandler.h***

Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.
**model.h baseClass, relates to modelGPX***

One function is overloaded with different signatures for the same function name.
**not***

One member function in an inherited class overrides a virtual base class member function.
**not***

One function is declared with a template that allows it to accept a generic parameter.
**not***

Memory Management
At least two variables are defined as references, or two functions use pass-by-reference in the project code.
**geodesic.h,UTM.h**

At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.
**modelGPX.h**


The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
**main.cpp,hull.cpp**

You need to update your readme in order to get this rubric reviewed :raised_hands:

For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.
**model.h,modelGPX.h**

For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
**main.cpp*

The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
**main.cpp, hull.h, model.h, modelGPX.h**

Concurrency
The project uses multiple threads in the execution.
**main.cpp done for visualization (all plots are generated at once and not loop by loop, fileWriting all files are written at once**

A promise and future is used to pass data from a worker thread to a parent thread in the project code.
**not**

A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
**model.h,hull.h**

A std::condition_variable is used in the project code to synchronize thread execution.
**not**



