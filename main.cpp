#include "GUI.h"
#include "CSRmatrix.h"
#include "Solvers.h"
#include <iostream>

int main()
{
    try{
//        GUI gui;
//        gui.run();
        CSRMatrix m1({1, 4, 9,3 , 5, 3, 1, 4},{0, 1, 3,3,2,2,0,3},{0,1,3,5,8}, 4, 4);
        CSRMatrix m2;
        m2.setDiag(1,4);
        std::cout << m1 << std::endl;
        std::cout.precision(10);
        std::cout <<"Matrix :" <<std::endl<< 2*m2+m1 << std::endl<< "Solution: " << std::endl <<  GaussZeidel(m2+m2+m1, {1, 1, 1, 1});
        return 0;
    } catch (std::runtime_error& er) {
        std::cout << "Zhenya what the fuck" << std::endl;
        std::cout << "The fuck is \"" << er.what() << "\"" << std::endl;
    } catch (std::exception& ex) {
        std::cout << "Some files are failed to be loaded" << std::endl;
    }
    return 0;
}

