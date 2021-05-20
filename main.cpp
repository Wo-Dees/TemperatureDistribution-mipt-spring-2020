#include "GUI.h"
#include "CSRmatrix.h"
#include "Solvers.h"
#include <iostream>
#include <fstream>
#include "difference_shame.h"
#include <queue>

int main()
{
    try{
        std::queue<vector<double>> data;
        solver_mesh(data, aluminum, 100, 100, 1, 500, 1, 0, 100);
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

