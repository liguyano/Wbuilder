cmake_minimum_required(VERSION 3.25)
project(wbuilder)

set(CMAKE_CXX_STANDARD 17)
set(LINK_DIR ./lib)
add_executable(wbuilder main.cpp  ProjectXml.cpp ProjectXml.h ProjectXml.h ScriptDealer.cpp ScriptDealer.h String.cpp String.h MyFile.cpp MyFile.h working/test/fff/aaa.h)

target_link_libraries(wbuilder xmlt)
add_library(xmlt STATIC tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp)