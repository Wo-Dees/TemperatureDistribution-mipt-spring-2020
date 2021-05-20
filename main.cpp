#include "GUI.h"
#include "CSRmatrix.h"
#include "Solvers.h"
#include <iostream>
#include <fstream>
#include <queue>

int main()
{
    try{
        GUI gui;
        gui.run();
    } catch (std::runtime_error& er) {
        std::cout << "Zhenya what the fuck" << std::endl;
        std::cout << "The fuck is \"" << er.what() << "\"" << std::endl;
    } catch (std::exception& ex) {
        std::cout << "Some files are failed to be loaded" << std::endl;
    }
    return 0;
}

