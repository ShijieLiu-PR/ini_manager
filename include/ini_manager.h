#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace ini{
typedef struct {
    std::string value;
    std::string comment;
}
ValueNode;

typedef std::map<std::string, ValueNode> KeyMap;
typedef std::map<std::string, Section> SectionMap;

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
    void SetComment(std::string comment);
    std::string GetComment();
    size_t Size();

    //key operations
    void AddKey(std::string name, std::string value, std::string comment = "");
    std::string GetKeyValue(std::string name);
    std::string GetkeyComment(std::string name);
    void SetKeyValue(std::string name, std::string value);
    void SetKeyComment(std::string name, std::string comment);
    bool IsKeyExist(std::string name);
    //operator[]
    std::string operator[](std::string name);
    //operator=
    Section &operator=(Section& setion);
};

class Ini_Manager{
private:
    std::string ini_file_path_;
    SectionMap section_map_;

public:
    Ini_Manager(std::string path);
    ~Ini_Manager();

    //section operations
    void AddSection(std::string name, Section section, std::string comment = "");
    Section GetSection(std::string name);
    std::string GetSectionComment(std::string name);
    void SetSectionComment(std::string name, std::string comment = "");
    //operator[]
    Section operator[](std::string name);
};

}//namespace ini
