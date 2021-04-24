//
// Created by Леонид Переверзин on 19.04.2021.
//

#include "special_number.h"
#include <iostream>
using std::cout;

// создать специальное число по мантисе и экспоненте (быстрая операция)
special_number::special_number(const double long& mantisa, const int short& exponenta) /* тест пройден */ {
    this->Mantisa = new double long(mantisa);
    this->Exponenta = new int short(exponenta);
}

// создать специальное число по какому-то long double (небыстрая операция, если знате как улучшить, пожалуйста, предложите)
special_number::special_number(const double long& number) /* тест пройден */ {
    double long mantisa = number;
    short int exponenta = 0;
    if (abs(number) >= (double long) 1) {
        while (abs(mantisa / (double long) 10) >= 1) {
            mantisa = mantisa / (double long) 10;
            exponenta++;
        }
        mantisa = mantisa / (double long) 10;
        exponenta++;
    }
    Mantisa = new double long(mantisa);
    Exponenta = new short int(exponenta);
}

// -_-
special_number::~special_number() /* тест пройден */{
    delete this->Mantisa;
    delete this->Exponenta;
}

// -_-
double long special_number::getMantisa() const /* тест пройден */ {
    return *(this->Mantisa);
}

// -_-
short int special_number::getExponenta() const /* тест пройден */ {
    return *(this->Exponenta);
}

// -_-
void special_number::setMantisa(const double long& mantisa) /* тест пройден */ {
    *(this->Mantisa) = mantisa;
}

// -_-
void special_number::setExponenta(const int short& exponenta) /* тест пройден */ {
    *(this->Exponenta) = exponenta;
}

// оператор сложения двух специальных чисел
special_number special_number::operator+(const special_number& second_term) /* тест пройден, но я бы на свежую голову ещё потестил, это с меня */ {
    if (*(second_term.Exponenta) >= *(this->Exponenta)) {
        if (abs((*(second_term.Mantisa) + *(this->Mantisa) * pow(10, *(this->Exponenta) - *(second_term.Exponenta)))) >= 1) {
            return special_number(*(second_term.Mantisa) / 10 + *(this->Mantisa) * pow(10, *(this->Exponenta) - 1 - *(second_term.Exponenta)), *(second_term.Exponenta) + 1);
        }
        else {
            return special_number(*(second_term.Mantisa) + *(this->Mantisa) * pow(10, *(this->Exponenta) - *(second_term.Exponenta)), *(second_term.Exponenta));
        }
    }
    else {
        if (abs(*(this->Mantisa) + *(second_term.Mantisa) * pow(10, *(second_term.Exponenta) -  *(this->Exponenta))) >= 1) {
            return special_number(*(this->Mantisa) / 10 + *(second_term.Mantisa) * pow(10, *(second_term.Exponenta) - *(this->Exponenta) - 1), *(this->Exponenta));
        }
        else {
            return special_number(*(this->Mantisa) + *(second_term.Mantisa) * pow(10, *(second_term.Exponenta) - *(this->Exponenta)), *(this->Exponenta));
        }
    }
}

// оператор вычитания двух специальных чисел
special_number special_number::operator-(const special_number& subtrahend) /* тест пройден, но я бы на свежую голову ещё потестил, это с меня */ {
    auto temp = special_number(-1) * subtrahend;
    return *this + temp;
}

// оператор умножения двух специальных чисел
special_number special_number::operator*(const special_number& second_multiplier) /* тест пройден */ {
    return special_number(*(this->Mantisa) * *(second_multiplier.Mantisa), *(this->Exponenta) + *(second_multiplier.Exponenta));
}

// оператор деления двух специальных чесел
special_number special_number::operator/(const special_number& divider) /* что то сломалось */ {
    if (*(divider.Mantisa) != 0) {
        if (*(this->Mantisa) <= *(divider.Mantisa))
            return special_number(*(this->Mantisa) / *(divider.Mantisa), *(this->Exponenta) - *(divider.Exponenta));
        else {
            while (*(this->Mantisa) > *(divider.Mantisa)) {
                *(this->Mantisa) = *(this->Mantisa) / 10;
                *(this->Exponenta)++;
            }
            return special_number(*(this->Mantisa) / *(divider.Mantisa), *(this->Exponenta) - *(divider.Exponenta));
        }
    }
    else {
        // пока тут заглушка, я хочу исключение добавить, у меня с ними как-то с первого раза не сложилось, я почитаю и добавлю
        return special_number(0, 0);
    }
}

// оператор вывода, можно использовать для отладки кода и вывод этих чисел в какой-нибудь файл
ostream& operator << (ostream& os, const special_number& number) /* тест пройден */ {
    os << number.getMantisa() << " " << number.getExponenta();
    return os;
}

// оператор ввода, можно использовать для отладки кода и на ввода из какого-ниубдь файла,
// возможно, пригодится для чего-нибудь весёлого и интересного, но это не точно
istream& operator >> (istream& is, special_number& number) /* тест пройден */ {
    double long mantisa;
    short int exponenta;
    is >> mantisa >> exponenta;
    number.setMantisa(mantisa);
    number.setExponenta(exponenta);
    return is;
}
