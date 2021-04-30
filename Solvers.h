#ifndef TEMPERATURE_SOLVERS
#define TEMPERATURE_SOLVERS

#include <stdexcept>
#include "CSRmatrix.h"
#include <cmath>

std::vector<double>operator-(vector<double> vec1, const vector<double> vec2)
{
    if (vec1.size() != vec2.size()) throw std::runtime_error("Debil");
    vector<double> res;
    res.reserve(vec1.size());
    for (int i = 0; i < vec2.size(); ++i)
        res.push_back(vec1[i] - vec2[i]);
    return res;
}

std::ostream &operator<<(std::ostream& os, std::vector<double> vector)
{
    for (double i : vector)
        os << "|| " << i << " ||"<<std::endl;
    return os;
}

double norm(const std::vector<double>& a){
    double sum = 0;
    for(double i : a){
        sum += i*i;
    }
    return sqrt(sum);
}

std::vector<double> Jacobi(const CSRMatrix& A, const vector<double>& b)
{
    vector<double> r(b.size());
    vector<double> x(b.size());
    vector<double> x_next(b.size());

    r = (A * x) - b;
    while(norm(r) > 0.00001)
    {
        for (unsigned i = 0; i < b.size(); ++i)
        {
            double sum = 0;
            for (int j = A.row_index[i]; j < A.row_index[i+1]; ++j)
                if (i != A.col[j]) sum += A.value[j] * x[A.col[j]];
            x_next[i] = ((b[i] - sum) / A(i,i));
        }
        x = x_next;
        r = (A * x) - b;
        std::cout << x <<std::endl;
    }
    return x;
}

#endif //TEMPERATURE_SOLVERS