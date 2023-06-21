//
// Created by kurum on 西暦2023年6月20日.
//

#include "ProjectXml.h"


ProjectXml::ProjectXml(std::string filePath1):filePath(filePath1) {
    project=new TiXmlDocument;
    project->LoadFile(filePath.c_str(),TIXML_ENCODING_UTF8);
    if (project->Error())
    {
        lnprint("end")
        lnprint(project->ErrorDesc());
        throw std::exception(project->ErrorDesc());
    }
    auto el=project->FirstChildElement("Project");
    auto target=el->FirstChildElement("Targets")->FirstChildElement("Target");
    auto group=target->FirstChildElement("Groups")->FirstChildElement("Group");
    files=group->FirstChildElement("Files");
    if (files==NULL)
    {
        throw std::exception("files is null");
    }
    files->Clear();
}

ProjectXml::~ProjectXml() {
    delete project;
}

void ProjectXml::addFile(std::string fileName, std::string filePath, std::string filetype) {
    /*
     *    <File>
              <FileName>main.c</FileName>
              <FileType>1</FileType>
              <FilePath>.\main.c</FilePath>
            </File>
     * */
    auto f=new TiXmlElement("File");
    auto FileName =new TiXmlElement("FileName");
    FileName->LinkEndChild(new TiXmlText(fileName.c_str()));
    auto FileType =new TiXmlElement("FileType");
    FileType->LinkEndChild(new TiXmlText(filetype.c_str()));
    auto FilePath =new TiXmlElement("FilePath");
    FilePath->LinkEndChild(new TiXmlText(filePath.c_str()));

    f->LinkEndChild(FileName);
    f->LinkEndChild(FileType);
    f->LinkEndChild(FilePath);

    files->LinkEndChild(f);
}

void ProjectXml::save() {
    project->SaveFile("./Project.uvproj");
}

void ProjectXml::addC(std::string fileName) {
    addFile(fileName+".c","./"+fileName+".c");
}

void ProjectXml::addH(std::string fileName) {
    addFile(fileName+".h","./"+fileName+".h","5");
}

