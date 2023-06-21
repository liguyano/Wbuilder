
#include "self_made.h"
#include "tinyxml/tinyxml.h"
#include "ProjectXml.h"
#include "ScriptDealer.h"
#include <filesystem>
using namespace std;

int main() {
    std::filesystem::path currentPath = std::filesystem::current_path();  // 获取当前路径
    std::cout << "当前路径是: " << currentPath << std::endl;
try
{
    ScriptDealer scriptDealer(currentPath.string()+"\\Project.uvproj");
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
