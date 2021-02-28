#include "fileHandler.h"
//////OsmoPoly
#include "tinyxml2.h"

#include "../model/node.h"
///STL
#include <iostream>
#include <string>
#include <cstddef>

fileHandler::fileHandler(std::string filePath) : _filePath(filePath)
{
  _doc = std::move(std::unique_ptr<tinyxml2::XMLDocument>(new tinyxml2::XMLDocument));
  _model = nullptr;
  _modelGPX = nullptr;
  _modelOSM = nullptr;
  _fileStatus = fileSuccess::notExecuted;

  std::size_t found = filePath.find_last_of("/\\");
  filePath = filePath.substr(found+1);
  std::size_t foundDot = filePath.find_last_of(".");
  filePath.erase(filePath.begin() + foundDot,filePath.end());
  _fileName = filePath;
}

fileHandler::~fileHandler()
{
  _doc.release();
}

void fileHandler::read()
{
    if(std::strstr(_filePath.c_str(),".gpx"))
      _dataType = dataType::GPX;
    else if(std::strstr(_filePath.c_str(),".osm"))
        _dataType = dataType::OSM;
    else
        _dataType = dataType::UNKNOWN;

    switch (_dataType)
    {
      case dataType::GPX:
      {
          _modelGPX = std::move(std::unique_ptr<modelGPX>(new modelGPX(_fileName)));
          readGPX();
          _modelGPX.get()->convertToXY();
          _fileStatus = fileSuccess::success;
          break;
      }
      case dataType::OSM:
      {
          _modelOSM = std::move(std::unique_ptr<modelOSM>(new modelOSM));
          readOSM();
          _modelOSM.get()->convertToXY();
          _fileStatus = fileSuccess::success;
          break;
      }
      case dataType::UNKNOWN:
      {
          _fileStatus = fileSuccess::fail;
          break;
      }
      }
}

fileHandler::dataType fileHandler::getDataType()
{
  return _dataType;
}

modelGPX *fileHandler::getModelGPX()
{
  return _modelGPX.get();
}

modelOSM *fileHandler::getModelOSM()
{
  return _modelOSM.get();
}

double fileHandler::getExtractionSize() const
{
    return extractionSize;
}

void fileHandler::setExtractionSize(double value)
{
    extractionSize = value;
}

fileHandler::fileSuccess fileHandler::getFilesStatus() const
{
    return _fileStatus;
}

void fileHandler::readGPX()
{
    using namespace tinyxml2;
    const char*c = _filePath.c_str();
    
    _doc.get()->LoadFile(c);
    // Let's make sure the file loaded fine...
  if (_doc.get()->ErrorID() == 0)
  {
      //Parse XML have not worked with tinyxml2 before parsing maybe improvable
      XMLNode* pRoot = _doc.get()->FirstChildElement();
      XMLElement* pElement = pRoot->FirstChildElement("trk");
      XMLElement* pEle2 = pElement->FirstChildElement("trkseg");
      XMLElement* pEle3 = pEle2->FirstChildElement("trkpt");

      double latitude, longitude, elevation;
      bool latitudeExist, longitudeExist;

      while (pEle3) // do as long there are trkpt tags
      {
          latitudeExist = pEle3->BoolAttribute("lat"); //check if lat tag exists
          longitudeExist = pEle3->BoolAttribute("lon");//check if lon tag exists

          if (latitudeExist == true && longitudeExist == true)
          {
              latitude = std::stod(pEle3->Attribute("lat"));
              longitude = std::stod(pEle3->Attribute("lon"));
              XMLElement* pElevation = pEle3->FirstChildElement("ele");
              if (pElevation != nullptr)//Elevation information is found
              {
                      elevation = std::stod(pElevation->GetText());
                      std::unique_ptr<node> geoNodePtr(new node(latitude,longitude,elevation));

                      _modelGPX.get()->setNode(std::move(geoNodePtr));

              }
              else //no elevation information is given so must be a nullPtr (I do not even know if this case can happen for grahpHopper)
              {
                  elevation = std::stod(pElevation->GetText());
                  std::unique_ptr<node> geoNodePtr(new node(latitude,longitude));
                  _modelGPX.get()->setNode(std::move(geoNodePtr));
              }
          }
          else
          {
                  std::cout <<" [FileHandler]: One of the Geonodes is missing latitude or longitude information. Check XML" << std::endl;
                  _model = nullptr;
                  return;
          }
          pEle3 = pEle3->NextSiblingElement("trkpt");
      }
  }
  else
  {
          std::cout << "[FileHandler]: bad xml" << std::endl;
          _model = nullptr;
          return;
  }

}

void fileHandler::readOSM()
{
  //2do
}
