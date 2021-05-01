//
// Created by evgen on 28.04.2021.
//

#ifndef MATRIX_CSRMATRIX_H
#define MATRIX_CSRMATRIX_H

#include <vector>
#include <iostream>
using std::vector;
using std::ostream;

// ОРГАНЗОВАТЬ НОРМАЛЬНЫЙ ВЕКТОР, А НЕ ЭТУ КАЛЕКУ (задачка Жене)
// ОБМАЗАТЬСЯ ИСКЛЧЕНИЯМИ (ещё задачка Жене)

class CSRMatrix {

    friend vector<double> Jacobi(const CSRMatrix& A, const vector<double>& b);
    friend vector<double> GaussZeidel(const CSRMatrix& A, const vector<double>& b);

private:
    vector<double> value;
    vector<unsigned int> col;
    vector<unsigned int> row_index;

    unsigned int Height;
    unsigned int Width;
    unsigned int NZ;

    double eps;

public:
    CSRMatrix(vector<double> value, vector<unsigned int> col, vector<unsigned int> row_index, unsigned int H,
              unsigned int W);

    CSRMatrix();

    ~CSRMatrix() = default;

    CSRMatrix transpose();

    double operator()(unsigned i, unsigned j) const;
    CSRMatrix operator+(const CSRMatrix &first_matrix) const;
    CSRMatrix operator- (const CSRMatrix& matrix) const;
    CSRMatrix operator*= (double k);
    friend ostream &operator<<(ostream &os, const CSRMatrix &matrix);
    friend ostream &operator<<(ostream &os, const CSRMatrix &&matrix);

    void getAsCSR(ostream &os);
    void setDiag(double element, unsigned N);
    unsigned int height();
    unsigned int width();

    CSRMatrix operator*(double k) const;
    friend CSRMatrix operator*(double k, const CSRMatrix& matrix);
    std::vector<double> operator*(const std::vector<double>& vector) const;
};

#endif //MATRIX_CSRMATRIX_H
