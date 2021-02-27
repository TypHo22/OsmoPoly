#include "modelGPX.h"
///STL
#include <iostream>
#include <fstream>
modelGPX::modelGPX(std::string fileName) : _fileName(fileName),_hull(nullptr)
{

}

modelGPX::~modelGPX()
{
   _hull.release();
}

hull *modelGPX::getHull() const
{
  return _hull.get();
}

void modelGPX::setHull( std::unique_ptr<hull> hull)
{
  _hull = std::move(hull);
}

void modelGPX::toExtractionFile()
{
  _mut.lock();

  std::ofstream myFile(_fileName + ".txt");

  std::vector<std::unique_ptr<node> >* const currentHull = _hull.get()->getHull();
  if(myFile.is_open())
  {
      myFile << _fileName << std::endl;
      myFile << "extractionArea" << std::endl;
      for(size_t a = 0; a < currentHull->size();a++)
      {
          myFile << currentHull->at(a).get()->getGeo().lon;
          myFile << "  ";
          myFile << currentHull->at(a).get()->getGeo().lat <<std::endl;
      }

    myFile << "END" << std::endl;
    myFile << "END" << std::endl;
    myFile.close();
  }

  _mut.unlock();
}

