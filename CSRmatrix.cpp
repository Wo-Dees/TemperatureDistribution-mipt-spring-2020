//
// Created by evgen on 28.04.2021.
//

#include "CSRmatrix.h"
#include <iostream>

CSRMatrix::CSRMatrix(vector<double> value, vector<unsigned int> col, vector<unsigned int> row_index, unsigned int H, unsigned int W) {
    this->col = std::move(col);
    this->row_index = std::move(row_index);
    this->value = std::move(value);
    this->Height = H;
    this->Width = W;
    this->NZ = this->value.size();
    this->eps = 1/100000.0;
}

CSRMatrix::CSRMatrix() {
    this->col = {};
    this->value= {};
    this->row_index = {};
    this->Height = 0;
    this->Width = 0;
    this->NZ = 0;
    this->eps = 1/100000.0;
}


void generate_zeros(ostream& os, unsigned int am)
{
    for (int i = 0; i < am; i++)
        os << "0 ";
}
ostream &operator<<(ostream &os, const CSRMatrix &matrix){ // <- working
    for (int i = 0; i < matrix.Height; i++)
    {
        os << "|| ";
        unsigned int begining_of_string = matrix.row_index[i];
        unsigned int endning_of_string = matrix.row_index[i+1];

        if (begining_of_string == endning_of_string) {
            generate_zeros(os, matrix.Width);
            os << "||" << std::endl;
            continue;
        }
        generate_zeros(os, matrix.col[begining_of_string]);
        os << matrix.value[begining_of_string] << " ";

        for(unsigned int k = begining_of_string + 1; k < endning_of_string; k++)
        {
            generate_zeros(os, matrix.col[k] - matrix.col[k-1] - 1);
            os << matrix.value[k] << " ";
        }
        if ((matrix.Width - matrix.col[endning_of_string - 1] - 1) >= 0)
            generate_zeros(os, (unsigned int)(matrix.Width - matrix.col[endning_of_string - 1]) - 1);
        os << "||" << std::endl;
    }
    return os;
}

CSRMatrix CSRMatrix::operator*(double k) const {
    vector<double> n_val;
    n_val.reserve(this->NZ);
    for (int i = 0; i < this->NZ; i++)
    {
        n_val.emplace_back(this->value[i]*k);
    }
    return CSRMatrix(n_val,this->col, this->row_index, this->Height, this->Width);
}

CSRMatrix operator*(double k, const CSRMatrix &matrix) {
    return matrix*k;
}

ostream &operator<<(ostream &os, const CSRMatrix &&matrix) { // <- working
    os << matrix;
    return os;
}

CSRMatrix CSRMatrix::operator+(const CSRMatrix &first_matrix) const{
    std::vector<double> val;
    std::vector<unsigned int> cols;
    std::vector<unsigned int> row_ind;
    row_ind.push_back(0);
    for (int i = 0; i < this->Height; i++) {
        unsigned int ending_of_first_string = first_matrix.row_index[i + 1];
        unsigned int ending_of_second_string = this->row_index[i+1];
        unsigned int element_in_first_string = first_matrix.row_index[i];;
        unsigned int element_in_second_string = this->row_index[i];

        int am_of_pushs = 0;

        while (element_in_first_string < ending_of_first_string || element_in_second_string < ending_of_second_string)
        {
            if (element_in_second_string < ending_of_second_string && element_in_first_string < ending_of_first_string) {
                double val1 = first_matrix.value[element_in_first_string];
                double val2 = this->value[element_in_second_string];
                unsigned int col1 = first_matrix.col[element_in_first_string];
                unsigned int col2 = this->col[element_in_second_string];
                if (col1 < col2) {
                    val.push_back(val1);
                    am_of_pushs++;
                    cols.push_back(col1);
                    element_in_first_string++;
                }
                if (col1 > col2) {
                    val.push_back(val2);
                    am_of_pushs++;
                    cols.push_back(col2);
                    element_in_second_string++;
                }
                if (col1 == col2) {
                    if (std::abs(val1 + val2) > CSRMatrix::eps) {
                        val.push_back(val2 + val1);
                        am_of_pushs++;
                        cols.push_back(col2);
                    }
                    element_in_first_string++;
                    element_in_second_string++;
                }
            }
            if (element_in_second_string < ending_of_second_string && element_in_first_string >= ending_of_first_string)
            {
                for (unsigned int elem = element_in_second_string; elem < ending_of_second_string; elem++)
                {
                    val.push_back(this->value[elem]);
                    am_of_pushs++;
                    cols.push_back(this->col[elem]);
                    element_in_second_string++;
                }
            }
            if (element_in_second_string >= ending_of_second_string && element_in_first_string < ending_of_first_string)
            {
                for (unsigned int elem = element_in_first_string; elem < ending_of_first_string; elem++)
                {
                    val.push_back(first_matrix.value[elem]);
                    am_of_pushs++;
                    cols.push_back(first_matrix.col[elem]);
                    element_in_first_string++;
                }
            }
        }
        row_ind.push_back(row_ind[i]+am_of_pushs);
    }
    return CSRMatrix(val, cols, row_ind, this->Height, this->Width);
}

void CSRMatrix::getAsCSR(ostream &os) {
    if (!this->value.empty()) {
        os << "Value: [";
        for (int i = 0; i < this->NZ - 1; i++)
            os << this->value[i] << ", ";
        os << this->value[this->NZ - 1] << "]" << std::endl;
    }else {
        os << "Value: [];" << std::endl;
    }

    if (!this->col.empty()) {
        os << "Col: [";
        for (int i = 0; i < this->NZ - 1; i++)
            os << this->col[i] << ", ";
        os << this->col[this->NZ - 1] << "]" << std::endl;
    }else {
        os << "Cols: [];" << std::endl;
    }

    if (!this->row_index.empty()) {
        os << "Row Index: [";
        for (int i = 0; i < this->Height; i++)
            os << this->row_index[i] << ", ";
        os << this->row_index[this->Height] << "]" << std::endl;
    }else {
        os << "Row Indexes [];" << std::endl;
    }
}

CSRMatrix CSRMatrix::operator*=(double k){
    for (int i = 0; i < this->NZ; i++)
    {
        this->value[i] *= k;
    }
    return *this;
}

CSRMatrix CSRMatrix::operator-(const CSRMatrix &matrix) const {
    return *this+(-1)*matrix;
}

CSRMatrix CSRMatrix::transpose() {

}

unsigned int CSRMatrix::height() {
    return this->Height;
}

unsigned int CSRMatrix::width() {
    return this->Width;
}

std::vector<double> CSRMatrix::operator*(const vector<double> &vector) const {
    std::vector<double> multi;
    for (unsigned int str_number = 0; str_number < this->Height; ++str_number)
    {
        double element = 0;
        for(unsigned int num_of_elem = this->row_index[str_number]; num_of_elem < this->row_index[str_number + 1] ; ++num_of_elem)
            element += this->value[num_of_elem] * vector[this->col[num_of_elem]];
        multi.push_back(element);
    }
    return multi;
}

void CSRMatrix::setDiag(double element, unsigned int N) {
    this->row_index.resize(0);
    this->col.resize(0);
    this->value.resize(0);

    for (unsigned i = 0; i < N; ++i)
    {
        this->value.push_back(element);
        this->col.push_back(i);
        this->row_index.push_back(i);
    }
    row_index.push_back(N);
    this->Height = this->Width = N;
    this->NZ = N;
}

double CSRMatrix::operator()(unsigned int i, unsigned int j) const{
    for (unsigned num_of_elem = this->row_index[i]; num_of_elem < this->row_index[i+1]; ++num_of_elem)
    {
        if (this->col[num_of_elem] == j)
            return this->value[num_of_elem];
    }
    return 0;
}
