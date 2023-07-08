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
    _findInclude(target);
    auto groups=target->FirstChildElement("Groups");
    groups->Clear();
    auto group=new TiXmlElement("Group");
    auto Gname=new TiXmlElement("GroupName");
    Gname->LinkEndChild(new TiXmlText("default"));
    auto fs=new TiXmlElement("Files");
    fs->LinkEndChild(new TiXmlText(""));
    group->LinkEndChild(Gname);
    group->LinkEndChild(fs);
    groups->LinkEndChild(group);
    files=fs;
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
TiXmlElement * ProjectXml::makeFile(std::string fileName, std::string filePath, std::string filetype)
{
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
    return f;
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

void ProjectXml::_findInclude(TiXmlElement *target) {
    auto TargetOption=target->FirstChildElement("TargetOption");
    auto Target51=TargetOption->FirstChildElement("Target51");
    if (Target51==NULL)
    {
        lnprint("It's a ARm project")
        auto TargetArmAds=TargetOption->FirstChildElement("TargetArmAds");
        auto Cads=TargetArmAds->FirstChildElement("Cads");
        auto VariousControls=Cads->FirstChildElement("VariousControls");
        include=VariousControls->FirstChildElement("IncludePath");
    } else
    {
        lnprint("It's a 51 project")
        auto C51=Target51->FirstChildElement("C51");
        auto VariousControls=C51->FirstChildElement("VariousControls");
        include=VariousControls->FirstChildElement("IncludePath");
    }

}

void ProjectXml::addInclude(std::string path) {
    std::string orienal_path;
    if (include->GetText()==NULL)
    {
        orienal_path="";
    }else
    {
        orienal_path=include->GetText();
    }

    include->Clear();
    include->LinkEndChild(new TiXmlText((orienal_path+path+";").c_str()));
}

