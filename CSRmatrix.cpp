//
// Created by evgen on 28.04.2021.
//

#include "CSRmatrix.h"
#include <iostream>
#include <algorithm>

CSRMatrix::CSRMatrix(vector<double> value, vector<unsigned int> col, vector<unsigned int> row_index, unsigned int H, unsigned int W) {
    if (row_index.size() != H+1) throw std::runtime_error("Invalid creation CSR (row_index.size != martrix height + 1)");
    if (value.size() != col.size()) throw std::runtime_error("Invalid creation CSR (udefined amount of not zero elements)");
    if (row_index[H] != col.size()) throw std::runtime_error("Invalid creation CSR (incorrect data)");
    if (*std::max_element(col.begin(), col.end()) >= W) throw std::runtime_error("Invalid creation CSR (incorrect data)");
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
        for (int j = 0; j < matrix.Width; j++)
            os << matrix(i, j) << " ";
        if (i != matrix.Height - 1) os << "||" << std::endl;
        else os << "||";
    }
    os <<"(" << matrix.Height << "x" << matrix.Width << ")"<<std::endl;
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
    std::vector<unsigned> using_cols(this->Width, -1); // массив для отмечаний уже использованных столбцов
    std::vector<unsigned> tmp_cols; //временный сol
    std::vector<unsigned> cols;  //будущий cols
    std::vector<unsigned> row_ind(this->Height + 1);
    std::vector<double> tmp_value; //временный массив значений сложенных строк
    std::vector<double> val;
    row_ind[0] = 0;
    // слияние индексов столбцов ненулевых элементов в один массив строки i
    for(size_t i = 0; i < this->Height; ++i) {
        tmp_value.resize(this->Width);
        for(unsigned j = this->row_index[i]; j < this->row_index[i + 1]; ++j){
            if(using_cols[this->col[j]] != i){
                using_cols[this->col[j]] = i;
                tmp_cols.emplace_back(this->col[j]);
            }
            tmp_value[this->col[j]] = this->value[j];
        }
        for(unsigned j = first_matrix.row_index[i]; j < first_matrix.row_index[i + 1]; ++j){
            if(using_cols[first_matrix.col[j]] != i){
                using_cols[first_matrix.col[j]] = i;
                tmp_cols.emplace_back(first_matrix.col[j]);
            }
            tmp_value[first_matrix.col[j]] += first_matrix.value[j];
        }
        for(const auto& j: tmp_cols){
            if(std::abs(tmp_value[j]) > this->eps ){
                cols.emplace_back(j);
                val.emplace_back(tmp_value[j]);
            } else continue;
        }
        row_ind[i + 1] = cols.size();
        tmp_cols.clear();
        tmp_value.clear();
    }
    CSRMatrix newmat(val, cols, row_ind, this->Height, this->Width);
    return newmat;
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
