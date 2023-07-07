//
// Created by kurum on 西暦2023年6月20日.
//

#ifndef WBUILDER_SCRIPTDEALER_H
#define WBUILDER_SCRIPTDEALER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "map"
#include "array"
#include "ProjectXml.h"
#include "String.h"

class ScriptDealer : public ProjectXml{
private:
    std::string respath;
    std::string headName;
    std::map<std::string,std::array<std::string,4>  > respos;
public:
    bool contains(const std::vector<std::string> &vec, std::string n);
    void setRespath(const std::string &respath);
    const std::string &getRespath() const;
    void read_res();
    bool copyFile( std::string sourceFile, std::string destinationFile);

private:
    void insertCustomStringAtFirstLine(std::string fileName, std::string customString);
    void splitFirstSpaceInFile(const std::string &fileName);
    std::string GetLastTwoCharacters(std::string& str);
    void addD(std::string path);
    std::vector<std::string> sections;
public:
    ScriptDealer(std::string filePath);
    void run();
};


#endif //WBUILDER_SCRIPTDEALER_H
