///OsmoPoly
#include "model/model.h"
#include "xml/fileHandler.h"
///STL
#include <memory>
#include <thread>
#include <future>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
///3rd Party

//Screen dimension constants
#include "math/hull.h"
#include <string>
#include <iostream>
//hullthickness

bool checkNum(std::string toCheck)
{
  for(size_t a = 0; a < toCheck.length();a++)
  {
    if(!isdigit(toCheck[a]))
    {
      std::cerr << "[Error] Non numeric value in size of Extraction Polynom"<<std::endl;
      throw std::runtime_error("");
    }

  }

  return true;
}

void checkInputArgSize(std::vector<std::string>& allArgs)
{
    size_t checkSum = (allArgs.size() - 1) % 2;
    if(checkSum != 0)
    {
        std::cerr << "[ERROR] Not enough input parameters"<<std::endl;
        throw std::runtime_error("");
    }
}

int main(int arc, char *argv[])
{
  std::vector<std::string> allArgs(argv, argv + arc);
  std::vector<std::unique_ptr<fileHandler>> files;

  try
  {
    checkInputArgSize(allArgs);
  }
  catch (std::runtime_error)
  {
      return -1;
  }

  for(size_t cFile = 1; cFile < arc; cFile++)
  {
     std::unique_ptr<fileHandler>f(new fileHandler(allArgs[cFile]));
     f.get()->read();

     try
     {
         checkNum(allArgs[cFile + 1]);
     }
     catch (std::runtime_error)
     {
         return -1;
     }

     const double thickness = std::stod(allArgs[cFile + 1]);
     f.get()->setExtractionSize(thickness);

     files.push_back(std::move(f));

     cFile++;
  }

  //lambda for gpx
  std::vector<std::thread> mPool;
  //process gpxHulls
  for(size_t b = 0; b < files.size();b++)
  {
      if(files.at(b).get()->getDataType() == fileHandler::dataType::GPX &&
              files.at(b).get()->getFilesStatus() == fileHandler::fileSuccess::success)
      {
        std::unique_ptr<hull>aHull (new hull(files[b].get()->getModelGPX()->getNodeHolder(),files[b].get()->getExtractionSize()));
        aHull.get()->calculateHull();

        fileHandler* mF = files.at(b).get();
        mF->getModelGPX()->setHull(std::move(aHull));

        auto visuLambda = [mF](){mF->getModelGPX()->getHull()->visualize();};
        mPool.emplace_back(std::thread(visuLambda));

        auto toFileLambda = [mF](){mF->getModelGPX()->toExtractionFile();};
        mPool.emplace_back(std::thread(toFileLambda));
      }
  }

  std::for_each(mPool.begin(),mPool.end(), [](std::thread& a){a.join();});
  return 0;
}
