
#include <string>
#include "../include/ini_manager.h"

namespace ini{
//constructor
Section::Section():name_(""),comment_(""){}
Section::Section(std::string name, std::string comment) : name_(name), comment_(comment) {}
//destructor
Section::~Section()
{
    name_.clear();
    comment_.clear();
    key_map_.clear();
}

void Section::SetName(std::string name)
{
    name_ = name;
}

std::string Section::GetName()
{
    return name_;
}

void Section::SetComment(std::string comment)
{
    comment_ = comment;
}

std::string Section::GetComment()
{
    return comment_;
}

size_t Section::Size()
{
    return key_map_.size();
}

//key operations
void Section::AddKey(std::string name, std::string value, std::string comment)
{
    if(name.size()>0)
    {
        key_map_[name].value = value;
        key_map_[name].comment = comment;
    }
}
std::string Section::GetKeyValue(std::string name)
{
    return key_map_[name].value;
}
std::string Section::GetkeyComment(std::string name)
{
    return key_map_[name].comment;
}
void Section::SetKeyValue(std::string name, std::string value)
{
    key_map_[name].value = value;
}
void Section::SetKeyComment(std::string name, std::string comment)
{
    key_map_[name].comment = comment;
}
bool Section::IsKeyExist(std::string name)
{
    return key_map_.count(name) > 0;
}

//operator[]
std::string Section::operator[](std::string name)
{
    return key_map_[name].value;
}

//operator=
Section& Section::operator=(Section& section)
{
    name_ = section.name_;
    comment_ = section.comment_;
    key_map_ = section.key_map_;
    return *this;
}

//class Ini_Manager
Ini_Manager::Ini_Manager(std::string path) : ini_file_path_(path) {};
Ini_Manager::~Ini_Manager()
{
    ini_file_path_.clear();
    section_map_.clear();
}

Section Ini_Manager::operator[](std::string name)
{
    return section_map_[name];
}


}//namespace ini