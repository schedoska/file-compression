// MIT License
//
// Copyright (c) 2019 yu-yama
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef ___MATRIX_INCLUDED_
#define ___MATRIX_INCLUDED_

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

template <typename T>
class Matrix;

template <typename T>
std::ostream& operator<<(std::ostream&, const Matrix<T>&);

template <typename T>
std::istream& operator>>(std::istream&,       Matrix<T>&);

template <typename T>
class Matrix {
    // typedef typename std::vector<T>::size_type size_type;
private:
    std::vector<T> mat = {};
    typename std::vector<T>::size_type n = 0, m = 0;

    std::tuple<Matrix, bool, typename std::vector<T>::size_type> gauss_count() const;
    Matrix basis() const;
    void resize_skip(typename std::vector<T>::size_type nn, typename std::vector<T>::size_type mm, typename std::vector<T>::size_type skipy, typename std::vector<T>::size_type skipx);

public:
    Matrix();
    Matrix(typename std::vector<T>::size_type n);
    Matrix(typename std::vector<T>::size_type n, typename std::vector<T>::size_type m);
    Matrix(std::vector<T> vecData);
    Matrix(std::vector< std::vector<T> > matData);
    Matrix(std::vector<T> matData, typename std::vector<T>::size_type n);
    Matrix(const Matrix& p);

    typename std::vector<T>::size_type row()    const { return n; }
    typename std::vector<T>::size_type column() const { return m; }

    std::vector<T> at_row   (typename std::vector<T>::size_type y) const;
    // std::vector<T*> at_row   (typename std::vector<T>::size_type y);
    std::vector<T> at_column(typename std::vector<T>::size_type x) const;
    // std::vector<T*> at_column(typename std::vector<T>::size_type x);
    T& at(typename std::vector<T>::size_type y, typename std::vector<T>::size_type x);
    const T& at(typename std::vector<T>::size_type y, typename std::vector<T>::size_type x) const;

    void push_row(std::vector<T> p);
    void pop_row();
    void push_column(std::vector<T> p);
    void pop_column();

    void append_rows(Matrix p);
    void remove_rows(typename std::vector<T>::size_type p);
    void append_columns(Matrix p);
    void remove_columns(typename std::vector<T>::size_type p);

    void insert_row(typename std::vector<T>::size_type p, std::vector<T> q);
    void delete_row(typename std::vector<T>::size_type p);
    void insert_column(typename std::vector<T>::size_type p, std::vector<T> q);
    void delete_column(typename std::vector<T>::size_type p);

    void insert_rows(typename std::vector<T>::size_type p, Matrix q);
    void delete_rows(typename std::vector<T>::size_type p, typename std::vector<T>::size_type q);
    void insert_columns(typename std::vector<T>::size_type p, Matrix q);
    void delete_columns(typename std::vector<T>::size_type p, typename std::vector<T>::size_type q);

    void resize(typename std::vector<T>::size_type nn);
    void resize(typename std::vector<T>::size_type nn, typename std::vector<T>::size_type mm);
    void resize(typename std::vector<T>::size_type nn, typename std::vector<T>::size_type mm, bool copy);
    Matrix  operator+() const;
    Matrix  operator-() const;

    std::vector<T> to_1d_vector() const;
    std::vector< std::vector<T> > to_2d_vector() const;

    Matrix& operator=(Matrix p);

    Matrix& operator+=(Matrix p);
    Matrix& operator-=(Matrix p);
    Matrix& operator*=(Matrix p);
    Matrix& operator*=(T p);
    Matrix& operator/=(Matrix p);
    Matrix& operator/=(T p);

    Matrix  operator+(Matrix p) const;
    Matrix  operator-(Matrix p) const;
    Matrix  operator*(Matrix p) const;
    Matrix  operator*(T p) const;
    // template <typename S>
    // friend Matrix<S> operator*(S n, const Matrix<S>& p);
    Matrix  operator/(Matrix p) const;
    Matrix  operator/(T p) const;
    // template <typename S>
    // friend Matrix<S> operator/(S n, const Matrix<S>& p);

    bool operator==(const Matrix& p) const;
    bool operator!=(const Matrix& p) const;

    bool empty() const;
    bool is_zero() const;
    bool is_identity() const;

    Matrix gauss() const;
    Matrix gauss_jordan() const;
    T det() const;
    Matrix inv() const;
    Matrix pow(int r) const;
    T trace() const;
    T rank() const;

    T norm_squared() const;
    double norm() const;
    double distance(Matrix p) const;
    double angle(Matrix p) const;

    T dot(Matrix p) const;
    bool orthogonal(Matrix p) const;
    Matrix projection(Matrix p) const;
    Matrix orthonormal() const;
    Matrix cross(Matrix p) const;

    T minor_at(typename std::vector<T>::size_type y, typename std::vector<T>::size_type x) const;
    T cofactor_at(typename std::vector<T>::size_type y, typename std::vector<T>::size_type x) const;
    Matrix<T> cofactor_matrix() const;
    Matrix<T> adjugate() const;

    Matrix transpose() const;

    std::string to_string() const;
    // std::string to_latex() const;

    friend std::ostream& operator<< <> (std::ostream&, const Matrix&);
    friend std::istream& operator>> <> (std::istream&,       Matrix&);
};

template <typename T>
std::ostream& operator<<(std::ostream& s, const Matrix<T>& x) {
    return s << x.to_string();
}

template <typename T>
std::istream& operator>>(std::istream& s,       Matrix<T>& x) {
    for (typename std::vector<T>::size_type i = 0; i < x.row(); ++i) for (typename std::vector<T>::size_type j = 0; j < x.column(); ++j) s >> x.at(i, j);
    return s;
}

template <typename T>
Matrix<T> identity_matrix(typename std::vector<T>::size_type n, T val) {
    Matrix<T> t(n, n);
    for (typename std::vector<T>::size_type i = 0; i < n; ++i) t.at(i, i) = (T)1;
    return t;
}

template <typename T>
std::vector<T> vdiff(std::vector<T> p, std::vector<T> q);
template <typename T>
std::vector<T> vscalar_mult(std::vector<T> p, T q);

template <typename T>
T vnorm_squared(std::vector<T> p);
template <typename T>
double vnorm(std::vector<T> p);
template <typename T>
double vdistance(std::vector<T> p, std::vector<T> q);
template <typename T>
double vangle(std::vector<T> p, std::vector<T> q);

template <typename T>
T vdot(std::vector<T> p, std::vector<T> q);
template <typename T>
bool vorthogonal(std::vector<T> p, std::vector<T> q);
template <typename T>
std::vector<T> vprojection(std::vector<T> p, std::vector<T> q);
template <typename T>
std::vector<T> vcross(std::vector<T> p, std::vector<T> q);

template <typename T>
class AugmentedMatrix {
private:
    Matrix<T> matl, matr;
    typename std::vector<T>::size_type n = 0, ml = 0, mr = 0;

public:
    AugmentedMatrix();
    AugmentedMatrix(typename std::vector<T>::size_type n, typename std::vector<T>::size_type ml);
    AugmentedMatrix(typename std::vector<T>::size_type n, typename std::vector<T>::size_type ml, typename std::vector<T>::size_type mr);
    AugmentedMatrix(Matrix<T> mmatl);
    AugmentedMatrix(Matrix<T> mmatl, Matrix<T> mmatr);
    AugmentedMatrix(const AugmentedMatrix& p);

    typename std::vector<T>::size_type row() const { return n; }
    typename std::pair<typename std::vector<T>::size_type, typename std::vector<T>::size_type> column() const { return {ml, mr}; }

    std::pair< std::vector<T>, std::vector<T> > at_row (typename std::vector<T>::size_type y) const;
    std::vector<T> at_column (typename std::vector<T>::size_type x) const;
    std::vector<T> at_columnl(typename std::vector<T>::size_type x) const;
    std::vector<T> at_columnr(typename std::vector<T>::size_type x) const;
    T& at(typename std::vector<T>::size_type y, typename std::vector<T>::size_type x);
    const T& at(typename std::vector<T>::size_type y, typename std::vector<T>::size_type x) const;

    Matrix<T> left() const;
    Matrix<T> right() const;

    void resize(typename std::vector<T>::size_type nn, typename std::vector<T>::size_type mml, typename std::vector<T>::size_type mmr);

    bool operator==(const AugmentedMatrix& p) const;
    bool operator!=(const AugmentedMatrix& p) const;

    AugmentedMatrix gauss() const;
    AugmentedMatrix gauss_jordan() const;
};

#endif
