//
// Created by Леонид Переверзин on 01.05.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_DIFFERENCE_SHAME_H
#define TEMPERATURE_DISTRIBUTION_DIFFERENCE_SHAME_H

#include <map>
#include <queue>
#include <vector>
#include "CSRmatrix.h"

using std::map;
using std::queue;
using std::vector;

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

// Уровень дискретизация
const unsigned int COUNT_STEP_LEN_X = 40; // будет 50 узлов сетки по x длине
const unsigned int COUNT_STEP_LEN_Y = 40; // будет 50 узлов сетки по y длине
const unsigned int COUNT_STEP_TIME = 2000; // будет 1000 узлов сетки по времени


void next_step(vector<double>& answer,  const vector<double>& before, const material& Material, const double& side_x, const double& side_y, const double& observation_time, const double& f, const double& p, const double& q)  {
    vector<double> value;
    vector<unsigned int> col;
    vector<unsigned int> row_index;
    vector<double> b;
    row_index.push_back(0);
    double D_x = (data_of_material.find(Material)->second * COUNT_STEP_LEN_X * COUNT_STEP_LEN_X) / (side_x * side_x);
    double D_y = (data_of_material.find(Material)->second * COUNT_STEP_LEN_Y * COUNT_STEP_LEN_Y) / (side_y * side_y);
    double D_m = - 2 * D_x - 2 * D_y - COUNT_STEP_TIME / observation_time;
    for (unsigned int step_x = 0; step_x < COUNT_STEP_LEN_X; ++step_x) {
        for (int unsigned step_y = 0; step_y < COUNT_STEP_LEN_Y; ++step_y) {
            if ((step_x == 0 && step_y == 0) || (step_x == 0 && step_y == COUNT_STEP_LEN_Y - 1) || (step_x == COUNT_STEP_LEN_X - 1 && step_y == COUNT_STEP_LEN_Y - 1) || (step_x == COUNT_STEP_LEN_X - 1 && step_y == 0)) {
                value.push_back(1);
                col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                b.push_back(f / p);
                row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 1);
            }
            else if (step_x == 0 || step_y == 0 || step_x == COUNT_STEP_LEN_X - 1 || step_y == COUNT_STEP_LEN_Y - 1) {
                if (step_x == 0) {
                    if (q != 0) {
                        b.push_back( - before[step_x * COUNT_STEP_LEN_Y + step_y] * COUNT_STEP_TIME / observation_time - f / q);
                        value.push_back(D_x);
                        value.push_back(D_x);
                        value.push_back(D_y + COUNT_STEP_TIME / observation_time);
                        value.push_back(D_m);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y - 1);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y + 1);
                        col.push_back((step_x + 1) * COUNT_STEP_LEN_Y + step_y);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                        row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 4);
                    }
                    else {
                        value.push_back(1);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                        b.push_back(f / p);
                        row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 1);
                    }
                }
                else if (step_y == 0) {
                    if (q != 0) {
                        value.push_back(D_y);
                        value.push_back(D_y);
                        value.push_back(D_x + COUNT_STEP_TIME / observation_time);
                        value.push_back(D_m);
                        col.push_back((step_x - 1) * COUNT_STEP_LEN_Y + step_y);
                        col.push_back((step_x + 1) * COUNT_STEP_LEN_Y + step_y);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y + 1);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                        b.push_back( - before[step_x * COUNT_STEP_LEN_Y + step_y] * COUNT_STEP_TIME / observation_time - f / q);
                        row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 4);
                    }
                    else {
                        value.push_back(1);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                        b.push_back(f / p);
                        row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 1);
                    }
                }
                else if (step_x == COUNT_STEP_LEN_X - 1) {
                    if (q != 0) {
                        value.push_back(D_x);
                        value.push_back(D_x);
                        value.push_back(D_x + COUNT_STEP_TIME / observation_time);
                        value.push_back(D_m);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y - 1);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y + 1);
                        col.push_back((step_x - 1) * COUNT_STEP_LEN_Y + step_y);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                        b.push_back( - before[step_x * COUNT_STEP_LEN_Y + step_y] * COUNT_STEP_TIME / observation_time - f / q);
                        row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 4);
                    }
                    else {
                        value.push_back(1);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                        b.push_back(f / p);
                        row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 1);
                    }

                }
                else {
                    if (q != 0) {
                        value.push_back(D_y);
                        value.push_back(D_y);
                        value.push_back(D_x + COUNT_STEP_TIME / observation_time);
                        value.push_back(D_m);
                        col.push_back((step_x - 1) * COUNT_STEP_LEN_Y + step_y);
                        col.push_back((step_x + 1) * COUNT_STEP_LEN_Y + step_y);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y - 1);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                        b.push_back( - before[step_x * COUNT_STEP_LEN_Y + step_y] * COUNT_STEP_TIME / observation_time - f / q);
                        row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 4);
                    }
                    else {
                        value.push_back(1);
                        col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                        b.push_back(f / p);
                        row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 1);
                    }
                }
            }
            else {
                value.push_back(D_x);
                value.push_back(D_x);
                value.push_back(D_y);
                value.push_back(D_y);
                value.push_back(D_m);
                col.push_back(step_x * COUNT_STEP_LEN_Y + step_y - 1);
                col.push_back(step_x * COUNT_STEP_LEN_Y + step_y + 1);
                col.push_back((step_x - 1) * COUNT_STEP_LEN_Y + step_y);
                col.push_back((step_x + 1) * COUNT_STEP_LEN_Y + step_y);
                col.push_back(step_x * COUNT_STEP_LEN_Y + step_y);
                b.push_back( - before[step_x * COUNT_STEP_LEN_Y + step_y] * COUNT_STEP_TIME / observation_time);
                row_index.push_back(row_index[step_x * COUNT_STEP_LEN_Y + step_y] + 5);
            };
        }
    }
    answer = GaussZeidel(CSRMatrix(value, col, row_index, COUNT_STEP_LEN_X * COUNT_STEP_LEN_Y, COUNT_STEP_LEN_X * COUNT_STEP_LEN_Y), b);
}

// Material - какой материал (то есть по сути коэффицен теплопроводности) (Вват / (м * Kельвин))
// Border_condition - скорость измениения темпеартуры на границе (граничные условия) (Кельвины / с)
// Initial_condition - начальная температура (начальные условия) (Кельвины)
// Side - сторона квадратной платинки (метры)
// Observation_time - время енаблюдения (секунды)

void solver_mesh(queue<vector<double>>& answer, const material& Material, const double& side_x, const double& side_y, const double& observation_time, const double& f, const double& p, const double& q, const double& t, const vector<double>& temperatute) {
    for (unsigned int step_time = 0; step_time < COUNT_STEP_TIME; ++step_time) {
        if (step_time == 0) {
            if (temperatute.size() == 1) {
                if (temperatute[0] == 0) {
                    vector<double> data(COUNT_STEP_LEN_X * COUNT_STEP_LEN_Y, t);
                    answer.push(std::move(data));
                }
                else {
                    vector<double> data;
                    for (unsigned int step_x = 0; step_x < COUNT_STEP_LEN_X; ++step_x) {
                        for (int unsigned step_y = 0; step_y < COUNT_STEP_LEN_Y; ++step_y) {
                            data.push_back((step_x * step_x + step_y * step_y) * t / (COUNT_STEP_LEN_Y * COUNT_STEP_LEN_Y + COUNT_STEP_LEN_X * COUNT_STEP_LEN_X));
                        }
                    }
                    answer.push(std::move(data));
                }
            }
            else {
//                answer.push(std::move(temperatute));
            }
        }
        else {
            vector<double> data;
            next_step(data, answer.back(), Material, side_x, side_y, observation_time, f, p, q);
            answer.push(std::move(data));
        }
    }
}

#endif //TEMPERATURE_DISTRIBUTION_DIFFERENCE_SHAME_H
