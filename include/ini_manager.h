#ifndef INCLUDE_INI_MANAGER_H
#define INCLUDE_INI_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

namespace ini{

//define line type enum

enum LineType{
    kCR=0,
    kComment,
    kSection,
    kKey,
    kOthers
};

//define key value node
typedef struct {
    std::string value;
    std::string comment;
}
ValueNode;

//define key map
typedef std::map<std::string, ValueNode> KeyMap;

class Section{
private:
    std::string name_;
    std::string comment_;
    KeyMap key_map_;

public:
    Section();
    Section(std::string name, std::string comment = "");
    ~Section();
    void SetName(std::string name);
    std::string GetName();
    void SetComment(std::string comment="");
    std::string GetComment();
    void AppendComment(std::string comment="\n");
    size_t Size();

    //key operations
    void AddKey(std::string name, std::string value, std::string comment = "");
    std::string GetKeyValue(std::string name);
    std::string GetkeyComment(std::string name);
    void SetKeyValue(std::string name, std::string value);
    void SetKeyComment(std::string name, std::string comment);
    bool IsKeyExist(std::string name);
    //format section into string
    std::string FormatSection();
    //operator[]
    std::string operator[](std::string name);
    //operator=
    Section &operator=(Section& setion);
};

// define section map
typedef std::map<std::string, Section *> SectionMap;
typedef std::map<std::string, Section *>::iterator SectionMapIter;

class Ini_Manager{
private:
    std::string ini_file_path_;
    SectionMap section_map_;



public:
    //constructor
    Ini_Manager(std::string path);
    //destructor
    ~Ini_Manager();
    //method
    void ImportIniFile();
    void ExportIniFile();
    static void TrimWhiteSpace(std::string& str, bool left = true, bool right = true);

    //Parse line type, for example, comment, section, key, and others which will be ignored
    LineType CheckLineType(std::string& str);

    //section operations
    void InsertSection(Section* ptr=nullptr);
    Section& GetSection(std::string sec_name);
    //operator[]
    Section& operator[](std::string name);
};

}//namespace ini

#endif