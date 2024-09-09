#include <iostream>
#include <string>
#include <vector>
#include "./include/ini_manager.h"

int main(int argc, char* argv[])
{
    std::string ini_path = "test\\config file.ini";
    ini::Ini_Manager ini_mgr(ini_path);
    ini_mgr.ImportIniFile();
    std::cout << ini_mgr["Function"]["Idd_Target_1P8V"] << std::endl;
    size_t count = ini_mgr.Size();
    std::vector<std::string> vec;
    ini_mgr["Basic"].GetKeyNames(vec);
    std::cout << ini_mgr.IsSectionExist("Basic") << std::endl;
    std::cout << ini_mgr.IsSectionExist("Trim") << std::endl;

    double x = ini_mgr["Function"].ToDouble("Idd_Target_1P8V");
    double y = ini_mgr["Function"].ToDouble("Idd_Limit_1P8V");

    std::cout << "x=" << x << std::endl;
    std::cout << "y=" << y << std::endl;
    return 0;
}