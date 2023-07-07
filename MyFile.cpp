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