#include <iostream>
#include <string>
#include <vector>
#include "./include/ini_reader.h"

int main(int argc, char* argv[])
{
    std::string ini_path = "test\\config file.ini";
    ini::Ini_Reader ini_mgr(ini_path);
    ini_mgr.ImportIniFile();
    std::vector<std::string> vec_secs;
    std::vector<std::string> vec_keys;

    ini_mgr.GetSectionNames(vec_secs);

    for (int i = 0; i < vec_secs.size();i++){
        std::cout << "[" << vec_secs[i] << "]" << std::endl;
        ini_mgr[vec_secs[i]].GetKeyNames(vec_keys);
        for (int j = 0; j < vec_keys.size();j++){
            std::cout << vec_keys[j] << " = ";
            std::cout << ini_mgr[vec_secs[i]][vec_keys[j]] << std::endl;
        }
        vec_keys.clear();
    }

        return 0;
}
