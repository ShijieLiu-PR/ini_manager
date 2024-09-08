#include <iostream>
#include <string>
#include "./include/ini_manager.h"

int main(int argc, char* argv[])
{
    std::string ini_path = "test\\config file.ini";
    ini::Ini_Manager ini_mgr(ini_path);
    ini_mgr.ImportIniFile();
    ini_mgr.ExportIniFile();
    return 0;
}