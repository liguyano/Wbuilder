//
// Created by kurum on 西暦2023年6月20日.
//

#ifndef WBUILDER_PROJECTXML_H
#define WBUILDER_PROJECTXML_H

#include "self_made.h"
#include <iostream>
#include "tinyxml/tinyxml.h"
class ProjectXml {
private:
    void _findInclude(TiXmlElement* target);
protected:
    TiXmlElement * files;
    TiXmlDocument* project;
    std::string filePath;
    TiXmlElement* include;
public:
     ProjectXml(std::string filePath="./Project.uvproj");
    void addFile(std::string fileName, std::string filePath, std::string filetype="1");
    void addC(std::string fileName);
    void addH(std::string fileName);
    void addInclude(std::string path);
    ~ProjectXml();
    void save();
    TiXmlElement *makeFile(std::string fileName, std::string filePath, std::string filetype);
};


#endif //WBUILDER_PROJECTXML_H
