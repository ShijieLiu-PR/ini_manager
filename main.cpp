#include <iostream>
#include "./include/ini_manager.h"

int main(int argc, char* argv[])
{
    ini::Section sec("basic", "#first section");
    sec.AddKey("VDD", "5.0");
    sec.AddKey("Mag_delay", "10");

    std::cout << "Hello World" << std::endl;
    return 0;
}