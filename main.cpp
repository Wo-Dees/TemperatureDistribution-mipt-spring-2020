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
//        GUI gui;
//        gui.run();
        // старая реализация разностной схемы
//        vector<vector<double>> data(COUNT_STEP_TIME);
//        difference_scheme(data, platinum, 100, 500, 100, 100);
//        // запись в файл
//        std::ofstream out;
//        out.open("/Users/leonidpereverzin/Desktop/Repositories/Temperature_distribution/data.txt");
//        out.precision(3);
//        for (auto item : data) {
//            for (unsigned int i = 0; i < COUNT_STEP_LEN; i++) {
//                for (unsigned int j = 0; j < COUNT_STEP_LEN; j++) {
//                    out << item[i * COUNT_STEP_LEN + j] << " ";
//                }
//                out << std::endl;
//            }
//            out << std::endl;
//        }
        std::queue<vector<double>> data;
        Border_Сonditions_Robin(data, platinum, 100, 20, 100, 100);
        // запись в файл
        std::ofstream out;
        out.open("/Users/leonidpereverzin/Desktop/Repositories/Temperature_distribution/data.txt");
        out.precision(4);
        for (unsigned int i = 0; i < COUNT_STEP_TIME; i++) {
            vector<double> item = data.front();
            data.pop();
            for (unsigned int i = 0; i < COUNT_STEP_LEN; i++) {
                for (unsigned int j = 0; j < COUNT_STEP_LEN; j++) {
                    out << item[i * COUNT_STEP_LEN + j] << " ";
                }
                out << std::endl;
            }
            out << std::endl;
        }
        // Чтобы в дальнейшем не возникло проблемы сразу оговорюсь,
        // что из очереди можно брать элементы только если их там не менее трёх 3,
        // потому что в один элемент файлы записваются, на основе предыдущего, то есть их push_back'ать
        // никак нельзя, а можно push_back'ать только предшествующий им, то есть третий.
        return 0;
    } catch (std::runtime_error& er) {
        std::cout << "Zhenya what the fuck" << std::endl;
        std::cout << "The fuck is \"" << er.what() << "\"" << std::endl;
    } catch (std::exception& ex) {
        std::cout << "Some files are failed to be loaded" << std::endl;
    }

    return 0;
}

