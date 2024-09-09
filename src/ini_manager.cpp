
#include <string>
#include <fstream>
#include <vector>
#include "../include/ini_manager.h"

namespace ini{

// #######################################################################################
// Class Section
// #######################################################################################

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

void Section::AppendComment(std::string comment)
{
    if(comment_.empty()){
        comment_ = comment;
    }
    else{
        comment_ = comment_ + '\n' + comment;
    }
}

size_t Section::Size()
{
    return key_map_.size();
}

double Section::ToDouble(std::string name)
{
    if(IsKeyExist(name)){
        return std::stof(key_map_[name].value);
    }
    return 0.0;
}

double Section::ToInt(std::string name){
    if(IsKeyExist(name)){
        return std::stoi(key_map_[name].value);
    }
    return 0;
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
void Section::GetKeyNames(std::vector<std::string>& vec){
    KeyMap::iterator it;
    for (it = key_map_.begin(); it != key_map_.end();it++){
        vec.push_back(it->first);
    }
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

std::string Section::FormatSection()
{
    std::string sec_str;
    KeyMap::iterator it;
    if(comment_.empty()){
        sec_str = '[' + name_ + ']';
    }
    else{
        sec_str = comment_ + '\n' + '[' + name_ + ']';
    }

    for (it = key_map_.begin(); it != key_map_.end();it++)
    {
        if(!it->second.comment.empty())
            sec_str += ('\n' + it->second.comment);
        sec_str += ('\n' + it->first + '=' + it->second.value);
    }
    return sec_str;
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

// #######################################################################################
// Class Ini_Manager
// #######################################################################################

// constructor
Ini_Manager::Ini_Manager(std::string path) : ini_file_path_(path) {};

//deconstructor
Ini_Manager::~Ini_Manager()
{
    ini_file_path_.clear();
    SectionMapIter iter;
    for (iter = section_map_.begin(); iter != section_map_.end(); iter++)
    {
        delete iter->second;
    }
}


//insert a new section
void Ini_Manager::InsertSection(Section* ptr)
{
    section_map_[ptr->GetName()] = ptr;
}

Section& Ini_Manager::GetSection(std::string sec_name)
{
    return *section_map_[sec_name];
}

//import ini file
void Ini_Manager::ImportIniFile()
{
    std::fstream fs;
    fs.open(ini_file_path_,std::ios::in);
    if(fs.is_open())
    {
        char* ptr_line = new char[1000];
        std::string str_line;
        //temp variable
        Section *ptr_section = nullptr;
        std::string comment = "";
        std::string section = "";
        std::string key = "";
        std::string value = "";

        while(!fs.eof())
        {
            fs.getline(ptr_line, 1000);
            str_line.assign(ptr_line);
            TrimWhiteSpace(str_line);
            switch (CheckLineType(str_line))
            {
            case kComment://Comment line
                if(comment.empty()){
                    comment = str_line;
                }
                else{
                    comment = comment + '\n' + str_line;
                }
                break;
            case kCR://carriage return line
                comment += '\n';
                break;
            case kSection://Section line
                str_line.erase(0, str_line.find_first_of('[') + 1);
                str_line.erase(str_line.find_first_of(']'), str_line.size() - str_line.find_first_of(']'));
                ptr_section = new Section(str_line, comment);
                InsertSection(ptr_section);
                comment = "";
                break;
            case kKey://Key line
                key = str_line.substr(0, str_line.find_first_of('='));
                TrimWhiteSpace(key);
                value = str_line.substr(str_line.find_first_of('=') + 1);
                TrimWhiteSpace(value);
                ptr_section->AddKey(key, value, comment);
                comment = "";
                break;
            default:
                break;
            }
        }
        delete[] ptr_line;
        fs.close();
    }
}

//void export ini file
void Ini_Manager::ExportIniFile(){
    std::string sec_str;
    SectionMapIter it = section_map_.begin();
    for (; it != section_map_.end();it++)
    {
        std::cout << it->second->FormatSection() << std::endl;
    }
}

//get all section names in this manager
void Ini_Manager::GetSectionNames(std::vector<std::string>& vec)
{
    SectionMapIter it;
    for (it = section_map_.begin(); it != section_map_.end();it++)
    {
        vec.push_back(it->first);
    }
}

size_t Ini_Manager::Size()
{
    return section_map_.size();
}
bool Ini_Manager::IsSectionExist(std::string sec_name)
{
    return section_map_.count(sec_name) > 0;
}

void Ini_Manager::TrimWhiteSpace(std::string& str, bool left, bool right)
{
    char white_space[] = " \r\n\t\v";
    if(left)
    {
        str.erase(0, str.find_first_not_of(white_space));
    }
    if(right)
    {
        str.erase(str.find_last_not_of(white_space) + 1, str.size() - str.find_last_not_of(white_space) - 1);
    }
}

LineType Ini_Manager::CheckLineType(std::string& str)
{
    //empty line is a carriage return
    if(str.size()==0)
        return kCR;
    //comment line starts with either '#' or ';'
    if(str.find_first_of('#') == 0 || str.find_first_of(';') == 0)
        return kComment;
    //section line starts with '[' and includes a ']' 
    if(str.find_first_of('[') == 0 && str.find_first_of(']')>1)
        return kSection;
    //key line
    if(str.find_first_of('=') > 0)
        return kKey;
    //except above cases
    return kOthers;
}

//operator[]
Section& Ini_Manager::operator[](std::string name)
{
    return *section_map_[name];
}


}//namespace ini