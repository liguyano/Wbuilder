
#include "self_made.h"
#include "tinyxml/tinyxml.h"
#include "ProjectXml.h"
#include "ScriptDealer.h"
#include <filesystem>
#include "encoding.h"

using namespace std;
std::string readFirstLine(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        if (getline(file, line)) {
            file.close();
            auto as=String::split(line," ");
            if (as[0]=="buildFile")
            {
                return "\\"+as[1];
            }else
            {
                return "\\Project.uvproj";
            }

        } else {
            file.close();
            return "\\Project.uvproj";;
        }
    } else {
        throw new exception(("open " +filename +"failded").c_str());
    }
}

int main() {
    system("chcp 65001");
    std::filesystem::path currentPath = std::filesystem::current_path();  // 获取当前路径
    std::cout << "当前路径是: " << currentPath << std::endl;
try
{
    ScriptDealer scriptDealer(currentPath.string()+ readFirstLine("./wmake.txt"));
    scriptDealer.read_res();
    lnprint(scriptDealer.getRespath());
    scriptDealer.run();
    scriptDealer.save();
}
catch (const std::exception &ex)
{
    lnprint(ex.what());
}
    return 0;
}
