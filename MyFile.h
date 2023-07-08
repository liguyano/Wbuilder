//
// Created by kurum on 2023/7/7.
//

#ifndef WBUILDER_MYFILE_H
#define WBUILDER_MYFILE_H
#include <filesystem>
#include <iostream>
std::vector<std::string> ListFiles(const std::string& path);
std::vector<std::string> GetFilesInFolder(std::string folderPath, std::string prefix = "");
#endif //WBUILDER_MYFILE_H
