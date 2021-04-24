//
// Created by Леонид Переверзин on 19.04.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_SPECIAL_NUMBER_H
#define TEMPERATURE_DISTRIBUTION_SPECIAL_NUMBER_H

#include <cmath>
#include <istream>
#include <ostream>

using std::ostream;
using std::istream;

class special_number {

private:

    long double* Mantisa; // мантиса специального числа
    short int* Exponenta; // экспонента специального числа

public:

    special_number(const double long& mantisa, const int short& exponenta); // конструктор специального число по мантисе и экспененте
    special_number(const long double& number); // конструктор специального число по числу в форме long double


    ~special_number(); // деструктор специального числа


    long double getMantisa() const; // возвращает экспоненту специального числа
    short int getExponenta() const; // возвращает мантиссу специального числа

    void setMantisa(const long double& mantisa); // устанавливает мантиссу специального числа
    void setExponenta(const short int& exponenta); // устанавливает экспоненту специального числа


    special_number operator + (const special_number& second_term); // оператор сложения специальных чисел
    special_number operator - (const special_number& subtrahend); // оператор вычитания специальных чисел
    special_number operator * (const special_number& second_multiplier); // оператор умножения специальных чисел
    special_number operator / (const special_number& divider); // оператор деления специальных чисел

};


ostream& operator << (ostream& os, const special_number& number);
istream& operator >> (istream& is, special_number& number);


#endif //TEMPERATURE_DISTRIBUTION_SPECIAL_NUMBER_H
