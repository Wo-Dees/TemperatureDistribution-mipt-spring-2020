#ifndef MATRIX_CSRMATRIX_H
#define MATRIX_CSRMATRIX_H

#include <vector>
#include <iostream>
using std::vector;
using std::ostream;

class CSRMatrix {
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

    ~CSRMatrix() = default;

    CSRMatrix operator+(const CSRMatrix &first_matrix);

    CSRMatrix operator*(double k) const;
    // <- два опертора позволяют работать с умножением с двух сторон
    friend CSRMatrix operator*(double k, const CSRMatrix& matrix);
    friend ostream &operator<<(ostream &os, CSRMatrix &matrix);
    friend ostream &operator<<(ostream &os, CSRMatrix &&matrix);

    void getAsCSR(ostream &os);
};


#endif //MATRIX_CSRMATRIX_H
