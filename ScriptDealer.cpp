//
// Created by kurum on 西暦2023年6月20日.
//

#include <filesystem>
#include "ScriptDealer.h"
#include "String.h"
#include "MyFile.h"
std::string ScriptDealer::GetLastTwoCharacters( std::string& str)
{
    if (str.length() >= 2)
    {
        return str.substr(str.length() - 2);
    }
    else
    {
        // 字符串长度小于2，返回整个字符串
        return str;
    }
}

void ScriptDealer::splitFirstSpaceInFile(const std::string &fileName) {
        std::ifstream inputFile(fileName); // Open file
        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                std::cout << "Full line content: " << line << std::endl;
                std::size_t spacePosition = line.find(' '); // Find space position
                if (spacePosition != std::string::npos) {
                    std::string firstPart = line.substr(0, spacePosition);
                    std::string secondPart = line.substr(spacePosition + 1);
                    std::cout << "Command: " << firstPart << std::endl;
                    std::size_t commaPosition = 0;
                    sections.clear();
                    while ((commaPosition = secondPart.find(',')) != std::string::npos) {
                        sections.push_back(secondPart.substr(0, commaPosition));
                        secondPart = secondPart.substr(commaPosition + 1);
                    }
                    sections.push_back(secondPart); // Add the remaining part
                    if (firstPart=="addC")
                    {
                        for (std::size_t idx = 0; idx < sections.size(); ++idx) {
                            std::cout << "add File " << (idx+1) << ": " << sections[idx] << std::endl;
                            addFile(sections[idx],"./"+sections[idx],"1");
                        }
                    }
                    if (firstPart=="addH")
                    {
                        for (std::size_t idx = 0; idx < sections.size(); ++idx) {
                            std::cout << "add File" << (idx+1) << ": " << sections[idx] << std::endl;
                            addFile(sections[idx],"./"+sections[idx],"5");
                        }
                    }
                    else
                    if (firstPart=="addClass")
                    {
                        for (std::size_t idx = 0; idx < sections.size(); ++idx) {
                            std::cout << "add Class" << (idx+1) << ": " << sections[idx] << std::endl;
                            addC(sections[idx] );
                            addH(sections[idx] );
                        }
                    }
                    else
                    if (firstPart=="use")
                    {
                        std::filesystem::path currentPath = std::filesystem::current_path();  // 获取当前路径
                        std::vector<std::string> added;
                        for (std::size_t idx = 0; idx < sections.size(); ++idx) {
                            if (contains(added,sections[idx]))
                            {
                                pr "skip ";
                                lnprint(sections[idx]);
                                continue;
                            }
                            std::cout << "use package" << (idx+1) << ": " << sections[idx] << std::endl;
                            added.push_back(sections[idx]);
                            auto arras=respos[sections[idx]];
                            if (arras[3]=="d")
                            {
                                goto addd;
                            }
                            if (arras[3]!="h")
                            {
                                addFile(arras[1]+".c",arras[0]+arras[1]+".c");
                            }
                            if (arras[3]!="c")
                            {
                                addFile(arras[1]+".h",arras[0]+arras[1]+".h","5");
                                insertCustomStringAtFirstLine(arras[0]+arras[1]+".h",headName);
                                copyFile(arras[0]+arras[1]+".h",currentPath.string()+"\\"+arras[1]+".h");
/*                                copyFile(arras[0]+arras[1]+".h","E:\\Keil_v5\\C251\\INC\\"+arras[1]+".h");
                                copyFile(arras[0]+arras[1]+".h","E:\\Keil_v5\\C51\\INC\\"+arras[1]+".h");*/
                                copyFile(arras[0]+arras[1]+".h","D:\\OneDrive - jxstnu.edu.cn\\keil\\respocity\\HEADS\\"+arras[1]+".h");
                            }
                            addd:
                            auto des=String::split(arras[2],",");
                            for (const auto &item: des)
                            {
                                    sections.push_back(item);
                            }
                        }
                    }
                    else if (firstPart=="addD")
                    {
                        addD("");
                    } else if (firstPart=="addDs")
                    {
                        for (std::size_t idx = 0; idx < sections.size(); ++idx) {
                            auto files=GetFilesInFolder("./"+sections[idx],"");
                            lnprint(files[0]);
                            for (int i = 0; i < files.size(); ++i) {
                                auto f=files[i];
                                if (GetLastTwoCharacters(f)==".c")
                                {
                                    lnprint("it's a .c file ")
                                    addFile(f,"./"+sections[idx]+"/"+f,"1");
                                }else if (GetLastTwoCharacters(f)==".h")
                                {
                                    lnprint("it's a .h file ")
                                    addFile(f,"./"+sections[idx]+"/"+f,"5");
                                }
                            }

                        }

                    }
                    if (firstPart=="setResP")
                    {
                        lnprint(sections[0]);
                        setRespath(sections[0]);
                    } else if (firstPart=="setIncludeHand")
                    {
                        headName="#include<"+sections[0]+">";
                    }
                    // Display the sections

                } else {
                    std::cout << "No space found to perform the split." << std::endl;
                }
            }
            inputFile.close(); // Close file
        } else {
            std::cout << "Unable to open file: " << fileName << std::endl;
        }
}

void ScriptDealer::run() {
    splitFirstSpaceInFile("wmake.txt");

}

ScriptDealer::ScriptDealer(std::string filePath) : ProjectXml(filePath){
respath="D:\\OneDrive - jxstnu.edu.cn\\keil\\respocity\\";
read_res();

}

const std::string &ScriptDealer::getRespath() const {
    return respath;
}

void ScriptDealer::setRespath(const std::string &respath)  {
    ScriptDealer::respath = respath;
}

void ScriptDealer::insertCustomStringAtFirstLine(std::string fileName, std::string customString) {

    std::ifstream inputFile(fileName);
    std::string tempFileName = "_temp.txt";
    std::ofstream outputFile(tempFileName);

    if (inputFile.is_open() && outputFile.is_open()) {
        std::string line;
        std::getline(inputFile, line); // Read and discard the first line

        outputFile << customString << std::endl; // Write the custom string to the first line of the temp file

        // Copy the remaining lines from the original file to the temp file
        while (std::getline(inputFile, line)) {
            outputFile << line << std::endl;
        }

        // Close and remove the original file
        inputFile.close();
        std::remove(fileName.c_str());

        // Close and rename the temp file to the original file name
        outputFile.close();
        std::rename(tempFileName.c_str(), fileName.c_str());

    } else {
        std::cerr << "Unable to open input file \"" << fileName << "\" or output file \"" << tempFileName << "\"" << std::endl;
    }
}

void ScriptDealer::read_res() {
    TiXmlDocument res;
    respos.clear();
    auto path=respath+"res.xml";
    res.LoadFile(path.c_str(),TIXML_ENCODING_UTF8);
    auto respo=res.FirstChildElement("respositorys");
    auto spo=respo->FirstChildElement("respository");
    while (spo)
    {
        std::array<std::string,4> a;
        a.at(0)=spo->FirstChildElement("path")->GetText();
        a.at(1)=spo->FirstChildElement("fileName")->GetText();
        if (spo->FirstChildElement("dependent"))
        {
            a.at(2)=spo->FirstChildElement("dependent")->GetText();
        }
        if (spo->Attribute("only"))
        {
            a.at(3)=spo->Attribute("only");
        }
        respos[spo->FirstChildElement("name")->GetText()]=a;
        spo=spo->NextSiblingElement();
    }
}

bool ScriptDealer::copyFile(std::string sourceFile, std::string destinationFile) {

    std::ifstream inFile(sourceFile, std::ios::binary);
    std::ofstream outFile(destinationFile, std::ios::binary);
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Unable to open source or destination file" << std::endl;
        return false;
    }
    outFile << inFile.rdbuf();
    outFile.close();
    inFile.close();
    return true;
}

bool ScriptDealer::contains(const std::vector<std::string> &vec, std::string n) {
    return std::find(vec.begin(), vec.end(), n) != vec.end();
}

void ScriptDealer::addD(std::string path) {
    for (std::size_t idx = 0; idx < sections.size(); idx+=2) {
        auto filess=ListFiles("./"+sections[idx]);
        lnprint(filess[0]);
        auto target= this->files->Parent()->Parent();
        auto Group=new TiXmlElement("Group");
        auto groupName=new TiXmlElement("GroupName");
        auto fis=new TiXmlElement("Files");
        if (filess.size()>0)
        {
            groupName->LinkEndChild(new TiXmlText(sections[idx+1].c_str()));
            Group->LinkEndChild(groupName);
            Group->LinkEndChild(fis);
            target->LinkEndChild(Group);
            addInclude(sections[idx]);
        }
        for (int i = 0; i < filess.size(); ++i) {
            auto f=filess[i];
            if (GetLastTwoCharacters(f)==".c")
            {
                lnprint("it's a .c file ")
                auto f1=makeFile(f,f,"1");
                pr "f";
                lnprint(f);
                fis->LinkEndChild(f1);
            }else if (GetLastTwoCharacters(f)==".h")
            {
                lnprint("it's a .h file ")
                fis->LinkEndChild( makeFile(f,f,"5"));
            }
        }

    }

}
