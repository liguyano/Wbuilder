//
// Created by kurum on 2023/7/7.
//


#include "MyFile.h"
namespace fs = std::filesystem;

std::vector<std::string> ListFiles(const std::string& path)
{
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            files.push_back(entry.path().string());
        }
    }

    return files;
}
std::vector<std::string> GetFilesInFolder(std::string folderPath,  std::string prefix )
{
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            std::string filePath = prefix + entry.path().filename().string();
            files.push_back(filePath);
        }
        else if (entry.is_directory())
        {
            std::string subFolderPath = entry.path().string();
            std::string subFolderPrefix = prefix + entry.path().filename().string() + "/";
            std::vector<std::string> subFiles = GetFilesInFolder(subFolderPath, subFolderPrefix);
            files.insert(files.end(), subFiles.begin(), subFiles.end());
        }
    }

    return files;
}
