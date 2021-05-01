#ifndef TEMPERATURE_SOLVERS
#define TEMPERATURE_SOLVERS

#include <cmath>
#include "Vector.h"

vector<double> Jacobi(const CSRMatrix& A, const vector<double>& b)
{
    if (A.Height != A.Width) throw std::runtime_error("Matrix isn't squared");
    for (unsigned i = 0; i < A.Height; i++)
        if (A(i,i) == 0) throw std::runtime_error("Zero on position (" + std::to_string(i) + ", " + std::to_string(i) + ")");

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
    }
    return x;
}

vector<double> GaussZeidel(const CSRMatrix& A, const vector<double>& b)
{
    if (A.Height != A.Width) throw std::runtime_error("Matrix isn't squared");
    for (unsigned i = 0; i < A.Height; i++)
        if (A(i,i) == 0) throw std::runtime_error("Zero on position (" + std::to_string(i) + ", " + std::to_string(i) + ")");

    vector<double> r(b.size());
    vector<double> x(b.size());

    r = (A * x) - b;
    while(norm(r) > 0.00001)
    {
        for (unsigned i = 0; i < b.size(); ++i)
        {
            double sum = 0;
            for (int j = A.row_index[i]; j < A.row_index[i+1]; ++j)
                if (i != A.col[j]) sum += A.value[j] * x[A.col[j]];
            x[i] = ((b[i] - sum) / A(i,i));
        }
        r = (A * x) - b;
    }
    return x;
}
#endif //TEMPERATURE_SOLVERS