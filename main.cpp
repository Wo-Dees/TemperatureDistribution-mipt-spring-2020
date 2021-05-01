#include "GUI.h"
#include <iostream>

int main()
{
    try{
        GUI gui;
        gui.run();
        return 0;
    } catch (std::runtime_error& er) {
        std::cout << "Zhenya what the fuck" << std::endl;
    } catch (std::exception& ex) {
        std::cout << "Some files are failed to be loaded" << std::endl;
    }
}

