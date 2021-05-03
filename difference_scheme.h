//
// Created by Леонид Переверзин on 01.05.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_DIFFERENCE_SCHEME_H
#define TEMPERATURE_DISTRIBUTION_DIFFERENCE_SCHEME_H

#include <map>

using std::map;

// возможные материалы
enum material {
    aluminum,
    iron,
    gold,
    brass,
    copper,
    platinum,
    silver,
    stell,
    mercury,
    titanium,
    lead,
    cast_iron
};

// материалы и их коэффиценты теплопроводности (Ватт/(метр*Kельвин))
const map <material, double> data_of_material = {{aluminum, 209.3}, {iron, 74.4}, {gold, 312.8},
                                           {brass, 85.5},{copper, 389.6}, {platinum, 70.0},
                                           {silver, 418.7}, {stell, 45.5}, {cast_iron, 62.8},
                                           {lead, 35.0}, {mercury, 29.1}, {titanium, 18.0}};

const unsigned int COUNT_STEP_LEN = 50; // будет 50 узлов сетки по длине
const unsigned int COUNT_STEP_TIME = 1000; // будет 1000 узлов сетки по времени

// тут лучше всего возвращать по референсу, но пока не судьба, солвер должен под это подстроиться
// temperature_at_sometime - распределение температур на предыдущем шаге
// Special_multiplier - оно мне просто нужно
// Border_condition - темпеартура на границе
vector<double> temperature_in_next_step(const vector<double>& temperature_at_sometime_0, vector<double>& temperature_at_sometime_1, const double& Special_multiplier, const double& Border_condition) {
    vector<double> value;
    vector<unsigned int> col;
    vector<unsigned int> row_index;
    vector<double> b;
    // переделать входящий вектор в CSR-ку и полуить столбец свободных членов
    for (unsigned int step_x = 0; step_x < COUNT_STEP_LEN; step_x++) {
        for (unsigned int step_y = 0; step_y < COUNT_STEP_LEN; step_y++) {
            if (step_x == 0 && step_y == 0) {
                row_index.push_back(0);
                value.push_back(1);
                col.push_back(COUNT_STEP_LEN * step_x + step_y);
                row_index.push_back(1);
                b.push_back(Border_condition);
            }
            else if (step_x == 0 || step_y == 0 || step_x == COUNT_STEP_LEN - 1 || step_y == COUNT_STEP_LEN - 1) {
                value.push_back(1);
                col.push_back(COUNT_STEP_LEN * step_x + step_y);
                row_index.push_back(1 + row_index[COUNT_STEP_LEN * step_x + step_y]);
                b.push_back(Border_condition);
            }
            else {
                // выглядит очень по-дурацки, но это мне позволяет не запутаться
                // загрузка значений
                value.push_back(1);
                value.push_back(1);
                value.push_back( - (4 + Special_multiplier));
                value.push_back(1);
                value.push_back(1);
                // загрузка столбцов;
                col.push_back(COUNT_STEP_LEN * step_x + step_y + 1);
                col.push_back(COUNT_STEP_LEN * step_x + step_y - 1);
                col.push_back(COUNT_STEP_LEN * step_x + step_y);
                col.push_back(COUNT_STEP_LEN * (step_x - 1) + step_y);
                col.push_back(COUNT_STEP_LEN * (step_x + 1) + step_y);
                // загрузка количтсва добавленных элементов
                row_index.push_back(5 + row_index[COUNT_STEP_LEN * step_x + step_y]);
                // загрузка свободного члена
                b.push_back(- temperature_at_sometime_0[step_y * COUNT_STEP_LEN + step_x] * Special_multiplier);
            }
        }
    }
    temperature_at_sometime_1 = GaussZeidel(CSRMatrix(value, col, row_index, COUNT_STEP_LEN * COUNT_STEP_LEN, COUNT_STEP_LEN * COUNT_STEP_LEN), b);
    return temperature_at_sometime_1;
}

// Material - какой материал (то есть по сути коэффицен теплопроводности) (Вват / (м * Kельвин))
// Border_condition - граничная температура (граничные условия) (Кельвины)
// Initial_condition - начальная температура (начальные условия) (Кельвины)
// Side - сторона квадратной платинки (пусть пока что платинка просто будет квадратная, чтобы не было проблем с отрисовкой и масштабированием)
vector<vector<double>>& difference_scheme(vector<vector<double>>& answer, const material& Material, const double& Initial_condition, const double& Border_condition, const double& Side, const double& Observation_time) {
    double special_multiplier = (Side * Side * COUNT_STEP_TIME) / (COUNT_STEP_LEN * COUNT_STEP_LEN * Observation_time * data_of_material.find(Material)->second); // специальный множетель - он мне будет нужен
    for (unsigned int step_time = 0; step_time < COUNT_STEP_TIME; step_time++) {
        if (step_time == 0) {
            for (unsigned int step_y = 0; step_y < COUNT_STEP_LEN; step_y++) {
                for (unsigned int step_x = 0; step_x < COUNT_STEP_LEN; step_x++) {
                    if ((step_x == 0) || (step_y == 0) || (step_x == COUNT_STEP_LEN - 1) || (step_y == COUNT_STEP_LEN - 1)) {
                        answer[step_time].push_back(Border_condition);
                    }
                    else {
                        answer[step_time].push_back(Initial_condition);
                    }
                }
            }
        }
        else {
            temperature_in_next_step(answer[step_time - 1], answer[step_time], special_multiplier, Border_condition);
        }
    }
    return answer; // возвращаю вектор из векторов, которые представляют из себя плотные матрицы размером COUNT_STEP_LEN * COUNT_STEP_LEN
}

#endif //TEMPERATURE_DISTRIBUTION_DIFFERENCE_SCHEME_H
