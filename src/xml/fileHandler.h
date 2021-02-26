#include "tinyxml2.h"
///STL
#include <string>
#include <memory>
#include "../model/model.h"
#include "../model/modelGPX.h"
#include "../model/modelOSM.h"


class fileHandler
{
public:
  fileHandler(std::string filePath);
  ~fileHandler();

  enum dataType
  {
    GPX,
    OSM,
    UNKNOWN
  };

  enum fileSuccess
  {
    notExecuted,
    fail,
    success,
  };

  void setPath();
  void read();
  dataType getDataType();

  //gpx
  modelGPX* getModelGPX();
  modelOSM* getModelOSM();

  double getExtractionSize() const;
  void setExtractionSize(double value);

private:
  std::unique_ptr<tinyxml2::XMLDocument> _doc;
  std::string _filePath;
    dataType _dataType;
    std::string _fileName;
    fileSuccess _fileStatus;
    std::unique_ptr<model> _model;
    std::unique_ptr<modelGPX> _modelGPX;
    std::unique_ptr<modelOSM> _modelOSM;
    double extractionSize;
    //methods
    void readGPX();
    void readOSM();

};

