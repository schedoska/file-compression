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

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "../include/matrix.h"

using namespace std;

template <class T>
Matrix<T>::Matrix() {
    resize(0, 0, false);
}

template <class T>
Matrix<T>::Matrix(typename vector<T>::size_type n) {
    resize(n, 1, false);
}

template <class T>
Matrix<T>::Matrix(typename vector<T>::size_type n, typename vector<T>::size_type m) {
    resize(n, m, false);
}

template <class T>
Matrix<T>::Matrix(vector<T> vecData) {
    mat = vecData;
    n = vecData.size();
    m = 1;
}

template <class T>
Matrix<T>::Matrix(vector< vector<T> > matData) {
    n = (typename vector<T>::size_type)matData.size();
    m = (typename vector<T>::size_type)0;
    for (typename vector< vector<T> >::size_type i = 0; i < n; ++i) m = max(m, (typename vector<T>::size_type)matData.at(i).size());
    mat = vector<T>(n * m);
    for (typename vector< vector<T> >::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < matData.at(i).size(); ++j) at((typename vector<T>::size_type)i, j) = matData.at(i).at(j);
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& p) {
    mat = p.mat;
    n = p.n;
    m = p.m;
}

template <class T>
vector<T> Matrix<T>::at_row (typename vector<T>::size_type y) const {
    if (y < 0 || y >= n) {
        ostringstream errMsg;
        errMsg << "The argument is out of range (" << y << "-th row is called for " << n << "x" << m << " matrix\n";
        throw out_of_range(errMsg.str());
    }
    vector<T> res(m);
    for (typename vector<T>::size_type i = 0; i < m; ++i) res.at(i) = at(y, i);
    return res;
}

// template <class T>
// vector<T*> Matrix<T>::at_row (typename vector<T>::size_type y) {
//     if (y < 0 || y >= n) {
//         ostringstream errMsg;
//         errMsg << "The argument is out of range (" << y << "-th row is called for " << n << "x" << m << " matrix\n";
//         throw out_of_range(errMsg.str());
//     }
//     vector<T*> res(m);
//     for (typename vector<T>::size_type i = 0; i < m; ++i) res.at(i) = &at(y, i);
//     return res;
// }

template <class T>
vector<T> Matrix<T>::at_column(typename vector<T>::size_type x) const {
    if (x < 0 || x >= m) {
        ostringstream errMsg;
        errMsg << "The argument is out of range (" << x << "-th column is called for " << n << "x" << m << " matrix\n";
        throw out_of_range(errMsg.str());
    }
    vector<T> res(n);
    for (typename vector<T>::size_type i = 0; i < n; ++i) res.at(i) = at(i, x);
    return res;
}

// template <class T>
// vector<T*> Matrix<T>::at_column(typename vector<T>::size_type x) {
//     if (x < 0 || x >= m) {
//         ostringstream errMsg;
//         errMsg << "The argument is out of range (" << x << "-th column is called for " << n << "x" << m << " matrix\n";
//         throw out_of_range(errMsg.str());
//     }
//     vector<T*> res(n);
//     for (typename vector<T>::size_type i = 0; i < n; ++i) res.at(i) = &at(i, x);
//     return res;
// }

template <class T>
T& Matrix<T>::at(typename vector<T>::size_type y, typename vector<T>::size_type x) {
    if (y < 0 || y >= n || x < 0 || x >= m) {
        ostringstream errMsg;
        errMsg << "The argument is out of range ((" << y << ", " << x << ") is called for " << n << "x" << m << " matrix\n";
        throw out_of_range(errMsg.str());
    }
    return mat.at(y * m + x);
}

template <class T>
const T& Matrix<T>::at(typename vector<T>::size_type y, typename vector<T>::size_type x) const {
    if (y < 0 || y >= n || x < 0 || x >= m) {
        ostringstream errMsg;
        errMsg << "The argument is out of range ((" << y << ", " << x << ") is called for " << n << "x" << m << " matrix\n";
        throw out_of_range(errMsg.str());
    }
    return mat.at(y * m + x);
}

template <class T>
void Matrix<T>::push_row(vector<T> p) {
    if (m != p.size()) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << 1 << "x" << p.size() << ")\n";
        throw invalid_argument(errMsg.str());
    }
    resize(n + 1);
    // Attention: the variable n is changed in "resize" method
    for (typename vector<T>::size_type j = 0; j < m; ++j) at(n - 1, j) = p.at(j);
}

template <class T>
void Matrix<T>::pop_row() {
    if (!n) {
        ostringstream errMsg;
        errMsg << "The matrix is empty\n";
        throw length_error(errMsg.str());
    }
    resize(n - 1);
}

template <class T>
void Matrix<T>::push_column(vector<T> p) {
    if (n != p.size()) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << p.size() << "x" << 1 << ")\n";
        throw invalid_argument(errMsg.str());
    }
    resize(n, m + 1);
    // Attention: the variable m is changed in "resize" method
    for (typename vector<T>::size_type i = 0; i < n; ++i) at(i, m - 1) = p.at(i);
}

template <class T>
void Matrix<T>::pop_column() {
    if (!m) {
        ostringstream errMsg;
        errMsg << "The matrix is empty\n";
        throw length_error(errMsg.str());
    }
    resize(n, m - 1);
}

template <class T>
void Matrix<T>::append_rows(Matrix<T> p) {
    if (m != p.m) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    typename vector<T>::size_type nc = n;
    resize(n + p.n);
    // Attention: the variable n is changed in "resize" method
    for (typename vector<T>::size_type i = 0; i < p.n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) at(i + nc, j) = p.at(i, j);
}

template <class T>
void Matrix<T>::remove_rows(typename vector<T>::size_type p) {
    if (n < p) {
        ostringstream errMsg;
        errMsg << "The number of rows being removed is exceeding the matrix (" << p << " rows from " << n << "x" << m << ")\n";
        throw length_error(errMsg.str());
    }
    resize(n - p);
}

template <class T>
void Matrix<T>::append_columns(Matrix<T> p) {
    if (n != p.n) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    typename vector<T>::size_type mc = m;
    resize(n, m + p.m);
    // Attention: the variable m is changed in "resize" method
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < p.m; ++j) at(i, j + mc) = p.at(i, j);
}

template <class T>
void Matrix<T>::remove_columns(typename vector<T>::size_type p) {
    if (m < p) {
        ostringstream errMsg;
        errMsg << "The number of columns being removed is exceeding the matrix (" << p << " columns from " << n << "x" << m << ")\n";
        throw length_error(errMsg.str());
    }
    resize(n, m - p);
}

template <class T>
void Matrix<T>::insert_row(typename vector<T>::size_type p, vector<T> q) {
    if (m != q.size()) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << 1 << "x" << q.size() << ")\n";
        throw invalid_argument(errMsg.str());
    }
    resize_skip(n + 1, m, p, m);
    for (typename vector<T>::size_type j = 0; j < m; ++j) at(p, j) = q.at(j);
}

template <class T>
void Matrix<T>::delete_row(typename vector<T>::size_type p) {
    if (!n) {
        ostringstream errMsg;
        errMsg << "The matrix is empty\n";
        throw length_error(errMsg.str());
    }
    resize_skip(n - 1, m, p, m);
}

template <class T>
void Matrix<T>::insert_column(typename vector<T>::size_type p, vector<T> q) {
    if (n != q.size()) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << q.size() << "x" << 1 << ")\n";
        throw invalid_argument(errMsg.str());
    }
    resize_skip(n, m + 1, n, p);
    for (typename vector<T>::size_type i = 0; i < n; ++i) at(i, p) = q.at(i);
}

template <class T>
void Matrix<T>::delete_column(typename vector<T>::size_type p) {
    if (!m) {
        ostringstream errMsg;
        errMsg << "The matrix is empty\n";
        throw length_error(errMsg.str());
    }
    resize_skip(n, m - 1, m, p);
}

template <class T>
void Matrix<T>::insert_rows(typename vector<T>::size_type p, Matrix<T> q) {
    if (m != q.m) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << q.n << "x" << q.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    resize_skip(n + q.n, m, p, m);
    for (typename vector<T>::size_type i = 0; i < q.n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) at(p + i, j) = q.at(i, j);
}

template <class T>
void Matrix<T>::delete_rows(typename vector<T>::size_type p, typename std::vector<T>::size_type q) {
    if (n < q) {
        ostringstream errMsg;
        errMsg << "The number of rows being removed is exceeding the matrix (" << q << " rows from " << n << "x" << m << ")\n";
        throw length_error(errMsg.str());
    }
    resize_skip(n - q, m, p, m);
}

template <class T>
void Matrix<T>::insert_columns(typename vector<T>::size_type p, Matrix<T> q) {
    if (n != q.n) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << q.n << "x" << q.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    resize_skip(n, m + q.m, n, p);
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < q.m; ++j) at(i, p + j) = q.at(i, j);
}

template <class T>
void Matrix<T>::delete_columns(typename vector<T>::size_type p, typename std::vector<T>::size_type q) {
    if (m < q) {
        ostringstream errMsg;
        errMsg << "The number of columns being removed is exceeding the matrix (" << q << " columns from " << n << "x" << m << ")\n";
        throw length_error(errMsg.str());
    }
    resize_skip(n, m - q, n, p);
}

template <class T>
void Matrix<T>::resize_skip(typename vector<T>::size_type nn, typename vector<T>::size_type mm, typename vector<T>::size_type skipy, typename vector<T>::size_type skipx) {
    if (n == nn && m == mm) return;
    // if n < nn, then (nn - n) rows from skipy-th row of return matrix are left as zero vectors
    // if n > nn, then (n - nn) rows from skipy-th row of argument matrix are removed
    // if m < mm, then (mm - m) columns from skipx-th column of return matrix are left as zero vectors
    // if m > mm, then (m - mm) columns from skipx-th column of argument matrix are removed
    vector<T> temp(nn * mm);
    typename vector<T>::size_type tempi, tempj;
    for (typename vector<T>::size_type i = 0; i < min(n, nn); ++i) {
        if (i < skipy) tempi = i;
        else if (i >= skipy + (n >= nn ? n - nn : 0)) tempi = i - (n - nn);
        else continue;
        for (typename vector<T>::size_type j = 0; j < min(m, mm); ++j) {
            if (j < skipx) tempj = j;
            else if (j >= skipx + (m >= mm ? m - mm : 0)) tempj = j - (m - mm);
            else continue;
            temp.at(tempi * mm + tempj) = mat.at(i * m + j);
        }
    }
    mat = temp;
    n = nn;
    m = mm;
}

template <class T>
void Matrix<T>::resize(typename vector<T>::size_type nn) {
    resize(nn, m);
}

template <class T>
void Matrix<T>::resize(typename vector<T>::size_type nn, typename vector<T>::size_type mm) {
    // vector<T> temp(nn * mm);
    // for (typename vector<T>::size_type i = 0; i < min(n, nn); ++i) for (typename vector<T>::size_type j = 0; j < min(m, mm); ++j) temp.at(i * mm + j) = mat.at(i * m + j);
    // mat = temp;
    // n = nn;
    // m = mm;
    resize_skip(nn, mm, n, m);
}

template <class T>
void Matrix<T>::resize(typename vector<T>::size_type nn, typename vector<T>::size_type mm, bool copy) {
    if (copy) resize_skip(nn, mm, n, m);
    else {
        mat = vector<T>(nn * mm);
        n = nn;
        m = mm;
    }
}

template <class T>
Matrix<T> Matrix<T>::operator+() const {
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix<T> t(*this);
    t *= -1;
    return t;
}

template <class T>
vector<T> Matrix<T>::to_1d_vector() const {
    if (n == 1 || m == 1) return mat;
    ostringstream errMsg;
    errMsg << "Argument is neither row nor column vector (" << n << "x" << m << ")\n";
    throw invalid_argument(errMsg.str());
}

template <class T>
vector< vector<T> > Matrix<T>::to_2d_vector() const {
    vector< vector<T> > temp(n, vector<T>(m));
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) temp.at((typename vector< vector<T> >::size_type)i).at(j) = at(i, j);
    return temp;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> p) {
    mat = p.mat;
    n = p.n;
    m = p.m;
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(Matrix<T> p) {
    if (n != p.n || m != p.m) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) at(i, j) += p.at(i, j);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(Matrix<T> p) {
    if (n != p.n || m != p.m) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) at(i, j) -= p.at(i, j);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T> p) {
    *this = *this * p;
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(T p) {
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) at(i, j) *= p;
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator/=(Matrix<T> p) {
    *this = *this / p;
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator/=(T p) {
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) at(i, j) /= p;
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> p) const {
    Matrix<T> t(*this);
    t += p;
    return t;
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> p) const {
    Matrix<T> t(*this);
    t -= p;
    return t;
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> p) const {
    if (m != p.n) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    Matrix<T> ans(n, p.m);
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) for (typename vector<T>::size_type k = 0; k < p.m; ++k) ans.at(i, k) += at(i, j) * p.at(j, k);
    return ans;
}

template <class T>
Matrix<T> Matrix<T>::operator*(T p) const {
    Matrix<T> t(*this);
    t *= p;
    return t;
}

// template <class T>
// Matrix<T> operator*(T n, const Matrix<T>& p) {
//     return p * n;
// }

template <class T>
Matrix<T> Matrix<T>::operator/(Matrix<T> p) const {
    return (*this) * p.inv();
}

template <class T>
Matrix<T> Matrix<T>::operator/(T p) const {
    Matrix<T> t(*this);
    t /= p;
    return t;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& p) const {
    if (n != p.n || m != p.m) return false;
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) if (at(i, j) != p.at(i, j)) return false;
    return true;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T>& p) const {
    return !(*this == p);
}

template <class T>
bool Matrix<T>::empty() const {
    return mat.empty();
}

template <class T>
bool Matrix<T>::is_zero() const {
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) if (at(i, j)) return false;
    return true;
}

template <class T>
bool Matrix<T>::is_identity() const {
    if (n != m) {
        ostringstream errMsg;
        errMsg << "Argument is not square matrix (" << n << "x" << m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    return (*this == identity_matrix(n, (T)1));
}

template <class T>
tuple<Matrix<T>, bool, typename vector<T>::size_type> Matrix<T>::gauss_count() const {
    Matrix<T> temp(*this);
    bool neg = false;
    typename vector<T>::size_type y = 0, x = 0;
    while (y < n && x < m) {
        typename vector<T>::size_type mPos = 0;
        T mVal = 0;
        for (typename vector<T>::size_type i = y; i < n; ++i) if (mVal < abs(temp.at(i, x))) mPos = i, mVal = abs(temp.at(i, x));
        if (!mVal) ++x;
        else {
            if (y != mPos) for (typename vector<T>::size_type j = 0; j < m; ++j) swap(temp.at(y, j), temp.at(mPos, j)), neg = !neg;
            for (typename vector<T>::size_type i = y + 1; i < n; ++i) {
                T f = temp.at(i, x) / temp.at(y, x);
                temp.at(i, x) = 0;
                for (typename vector<T>::size_type j = x + 1; j < m; ++j) temp.at(i, j) -= temp.at(y, j) * f;
            }
            ++y, ++x;
        }
    }
    return make_tuple(temp, neg, y);
}

template <class T>
Matrix<T> Matrix<T>::gauss() const {
    return get<0>(gauss_count());
}


template <class T>
Matrix<T> Matrix<T>::gauss_jordan() const {
    Matrix<T> temp = gauss();
    vector<typename vector<T>::size_type> lPos;
    lPos.reserve(m);
    typename vector<T>::size_type y = 0;
    for (typename vector<T>::size_type j = 0; y < n && j < m; ++j) if (temp.at(y, j)) lPos.push_back(j), ++y;
    --y;
    for (; y >= 0 && y < n; --y) {
        typename vector<T>::size_type x = lPos.at(y);
        for (typename vector<T>::size_type j = x + 1; j < m; ++j) temp.at(y, j) /= temp.at(y, x);
        temp.at(y, x) = 1;
        for (typename vector<T>::size_type i = 0; i < y; ++i) {
            for (typename vector<T>::size_type j = x + 1; j < m; ++j) temp.at(i, j) -= temp.at(y, j) * temp.at(i, x);
            temp.at(i, x) = 0;
        }
    }
    return temp;
}

template <class T>
T Matrix<T>::det() const {
    if (n != m) {
        ostringstream errMsg;
        errMsg << "Argument is not square matrix (" << n << "x" << m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    tuple<Matrix<T>, bool, typename vector<T>::size_type> temp = gauss_count();
    T ans = (get<1>(temp) ? -1 : 1);
    for (typename vector<T>::size_type i = 0; i < n; ++i) ans *= get<0>(temp).at(i, i);
    return ans;
}

template <class T>
Matrix<T> Matrix<T>::inv() const {
    if (n != m) {
        ostringstream errMsg;
        errMsg << "Argument is not square matrix (" << n << "x" << m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    AugmentedMatrix<T> temp1((*this), identity_matrix(n, (T)1));
    AugmentedMatrix<T> temp2 = temp1.gauss_jordan();
    if (temp2.left() != identity_matrix(n, (T)1)) {
        ostringstream errMsg;
        errMsg << "Argument is not invertible\n";
        throw invalid_argument(errMsg.str());
    }
    return temp2.right();
}

template <class T>
Matrix<T> Matrix<T>::pow(int r) const {
    if (n != m) {
        ostringstream errMsg;
        errMsg << "Argument is not square matrix (" << n << "x" << m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    if (r < 0) return inv().pow(-r);
    else if (!r) return identity_matrix(n, (T)1);
    else if (r % 2) return pow(r - 1) * (*this);
    else {
        Matrix<T> t = pow(r / 2);
        return t * t;
    }
}

template <class T>
T Matrix<T>::trace() const {
    if (n != m) {
        ostringstream errMsg;
        errMsg << "Argument is not square matrix (" << n << "x" << m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    T ans = 0;
    for (typename vector<T>::size_type i = 0; i < n; ++i) ans += at(i, i);
    return ans;
}

template <class T>
T Matrix<T>::rank() const {
    return get<2>(gauss_count());
}

template <class T>
vector<T> vdiff(vector<T> p, vector<T> q) {
    if (p.size() != q.size()) {
        ostringstream errMsg;
        errMsg << "Sizes of vectors do not match (" << p.size() << ", " << q.size() << ")\n";
        throw invalid_argument(errMsg.str());
    }
    vector<T> t(p);
    for (typename vector<T>::size_type i = 0; i < p.size(); ++i) t.at(i) -= q.at(i);
    return t;
}

template <class T>
vector<T> vscalar_mult(vector<T> p, T q) {
    vector<T> t(p);
    for (typename vector<T>::size_type i = 0; i < p.size(); ++i) t.at(i) *= q;
    return t;
}

template <class T>
T vnorm_squared(vector<T> p) {
    T ans = 0;
    for (typename vector<T>::size_type i = 0; i < p.size(); ++i) ans += p.at(i) * p.at(i);
    return ans;
}

template <class T>
T Matrix<T>::norm_squared() const {
    return vnorm_squared(to_1d_vector());
}

template <class T>
double vnorm(vector<T> p) {
    return sqrt((double)vnorm_squared(p));
}

template <class T>
double Matrix<T>::norm() const {
    return sqrt((double)norm_squared());
}

template <class T>
double vdistance(vector<T> p, vector<T> q) {
    return vnorm(vdiff(p, q));
}

template <class T>
double Matrix<T>::distance(Matrix<T> p) const {
    return (*this - p).norm();
}

template <class T>
double vangle(vector<T> p, vector<T> q) {
    return acos((double)vdot(p, q) / vnorm(p) / vnorm(q));
}

template <class T>
double Matrix<T>::angle(Matrix<T> p) const {
    return acos((double)dot(p) / norm() / p.norm());
}

template <class T>
T vdot(vector<T> p, vector<T> q) {
    if (p.size() != q.size()) {
        ostringstream errMsg;
        errMsg << "Sizes of vectors do not match (" << p.size() << ", " << q.size() << ")\n";
        throw invalid_argument(errMsg.str());
    }
    T ans = 0;
    for (typename vector<T>::size_type i = 0; i < p.size(); ++i) ans += p.at(i) * q.at(i);
    return ans;
}

template <class T>
T Matrix<T>::dot(Matrix<T> p) const {
    if (n != p.n || m != p.m) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
        throw invalid_argument(errMsg.str());
    } else if (n != 1 && m != 1) {
        ostringstream errMsg;
        errMsg << "Arguments are neither row nor column vector (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    return vdot(to_1d_vector(), p.to_1d_vector());
}

template <class T>
bool vorthogonal(vector<T> p, vector<T> q) {
    return (vdot(p, q) == 0);
}

template <class T>
bool Matrix<T>::orthogonal(Matrix<T> p) const {
    return (dot(p) == 0);
}

template <class T>
vector<T> vprojection(vector<T> p, vector<T> q) {
    return vscalar_mult(q, (T)(vdot(p, q) / vnorm_squared(q)));
}

template <class T>
Matrix<T> Matrix<T>::projection(Matrix<T> p) const {
    return p * (dot(p) / p.norm_squared());
}

template <class T>
Matrix<T> Matrix<T>::basis() const {
    Matrix<T> temp1;
    typename vector<T>::size_type temp2;
    tie(temp1, ignore, temp2) = transpose().gauss_count();
    temp1.resize(temp2);
    return temp1;
}

template <class T>
Matrix<T> Matrix<T>::orthonormal() const {
    Matrix<T> temp(*this);
    vector<typename vector<T>::size_type> zero_columns;
    for (typename vector<T>::size_type j = 0; j < m; ++j) {
        for (typename vector<T>::size_type jj = 0; jj < j; ++jj) {
            vector<T> proj = vprojection(at_column(j), temp.at_column(jj));
            for (typename vector<T>::size_type i = 0; i < n; ++i) temp.at(i, j) -= proj.at(i);
        }
        double column_norm = vnorm(at_column(j));
        bool is_zero_column = true;
        for (typename vector<T>::size_type i = 0; i < n; ++i) if (temp.at(i, j)) temp.at(i, j) /= column_norm, is_zero_column = false;
        if (is_zero_column) zero_columns.push_back(j);
    }
    while (zero_columns.size()) {
        temp.delete_column(zero_columns.back());
        zero_columns.pop_back();
    }
    return temp;
}

template <class T>
vector<T> vcross(vector<T> p, vector<T> q) {
    if (p.size() != 3 || q.size() != 3) {
        ostringstream errMsg;
        errMsg << "Arguments do not both have exactly three elements (" << p.size() << ", " << q.size() << ")\n";
        throw invalid_argument(errMsg.str());
    }
    vector<T> ans(3);
    for (typename vector<T>::size_type i = 0; i < 3; ++i) ans.at(i) = p.at((i + 1) % 3) * q.at((i + 2) % 3) - p.at((i + 2) % 3) * q.at((i + 1) % 3);
    return ans;
}

template <class T>
Matrix<T> Matrix<T>::cross(Matrix<T> p) const {
    if (n != p.n || m != p.m) {
        ostringstream errMsg;
        errMsg << "Dimensions of matrices do not match (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    if ((n == 1 && m == 3) || (n == 3 && m == 1)) return Matrix<T>(vcross(to_1d_vector(), p.to_1d_vector()));
    ostringstream errMsg;
    errMsg << "Arguments are neither 3x1 nor 1x3 vector (" << n << "x" << m << ", " << p.n << "x" << p.m << ")\n";
    throw invalid_argument(errMsg.str());
}

template <class T>
T Matrix<T>::minor_at(typename vector<T>::size_type y, typename vector<T>::size_type x) const {
    if (n != m) {
        ostringstream errMsg;
        errMsg << "Argument is not square matrix (" << n << "x" << m << ")\n";
        throw invalid_argument(errMsg.str());
    }
    Matrix<T> temp(n - 1, m - 1);
    for (typename vector<T>::size_type i = 0; i < n; ++i) {
        if (y == i) continue;
        for (typename vector<T>::size_type j = 0; j < m; ++j) {
            if (x == j) continue;
            temp.at(i - (i > y), j - (j > x)) = at(i, j);
        }
    }
    return temp.det();
}

template <class T>
T Matrix<T>::cofactor_at(typename vector<T>::size_type y, typename vector<T>::size_type x) const {
    return minor_at(y, x) * ((y + x) % 2 ? -1 : 1);
}

template <class T>
Matrix<T> Matrix<T>::cofactor_matrix() const {
    Matrix<T> temp(n, m);
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) temp.at(i, j) = cofactor_at(i, j);
    return temp;
}

template <class T>
Matrix<T> Matrix<T>::adjugate() const {
    return cofactor_matrix().transpose();
}

template <class T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> temp(m, n);
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) temp.at(j, i) = at(i, j);
    return temp;
}

template <class T>
string Matrix<T>::to_string() const {
    ostringstream s;
    for (typename vector<T>::size_type i = 0; i < n; ++i) for (typename vector<T>::size_type j = 0; j < m; ++j) s << at(i, j) << (j == m - 1 ? "\n" : ", ");
    return s.str();
    // Count the number of digits of each component in a column, and forms matrix using ascii art
    // for (typename vector<T>::size_type j = 0; j < m; ++j) {
    //     string::size_type m = 0;
    //     for (typename vector<T>::size_type i = 0; i < n; ++i) m = max(m, to_string(at(i, j)).size())
    // }
}

template class Matrix<short>;
// template class Matrix<unsigned short>;
template class Matrix<int>;
// template class Matrix<unsigned int>;
template class Matrix<long>;
// template class Matrix<unsigned long>;
template class Matrix<long long>;
// template class Matrix<unsigned long long>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long double>;

template <class T>
AugmentedMatrix<T>::AugmentedMatrix() {
    resize(0, 0, 0);
}

template <class T>
AugmentedMatrix<T>::AugmentedMatrix(typename vector<T>::size_type n, typename vector<T>::size_type ml) {
    resize(n, ml, 1);
}

template <class T>
AugmentedMatrix<T>::AugmentedMatrix(typename vector<T>::size_type n, typename vector<T>::size_type ml, typename vector<T>::size_type mr) {
    resize(n, ml, mr);
}

template <class T>
AugmentedMatrix<T>::AugmentedMatrix(Matrix<T> mmatl) {
    matl = mmatl;
    matr = Matrix<T>(mmatl.row());
    n = mmatl.row();
    ml = mmatl.column();
    mr = 1;
}

template <class T>
AugmentedMatrix<T>::AugmentedMatrix(Matrix<T> mmatl, Matrix<T> mmatr) {
    if (mmatl.row() != mmatr.row()) {
        ostringstream errMsg;
        errMsg << "The number of rows does not match (" << mmatl.row() << "x" << mmatl.column() << ", " << mmatr.row() << "x" << mmatr.column() << ")\n";
        throw invalid_argument(errMsg.str());
    }
    matl = mmatl;
    matr = mmatr;
    n = mmatl.row();
    ml = mmatl.column();
    mr = mmatr.column();
}

template <class T>
AugmentedMatrix<T>::AugmentedMatrix(const AugmentedMatrix& p) {
    matl = p.matl;
    matr = p.matr;
    n = p.n;
    ml = p.ml;
    mr = p.mr;
}

template <class T>
pair< vector<T>, vector<T> > AugmentedMatrix<T>::at_row (typename vector<T>::size_type y) const {
    if (y < 0 || y >= n) {
        ostringstream errMsg;
        errMsg << "The argument is out of range (" << y << "-th row is called for [" << n << "x" << ml << "|" << n << "x" << mr << "] augmented matrix\n";
        throw out_of_range(errMsg.str());
    }
    return make_pair(matl.at_row(y), matr.at_row(y));
}

template <class T>
vector<T> AugmentedMatrix<T>::at_column (typename vector<T>::size_type x) const {
    if (x < 0 || x >= ml + mr) {
        ostringstream errMsg;
        errMsg << "The argument is out of range (" << x << "-th column is called for [" << n << "x" << ml << "|" << n << "x" << mr << "] augmented matrix\n";
        throw out_of_range(errMsg.str());
    }
    if (x < ml) return at_columnl(x);
    else return at_columnr(x - ml);
}

template <class T>
vector<T> AugmentedMatrix<T>::at_columnl(typename vector<T>::size_type x) const {
    return matl.at_column(x);
}

template <class T>
vector<T> AugmentedMatrix<T>::at_columnr(typename vector<T>::size_type x) const {
    return matr.at_column(x);
}

template <class T>
T& AugmentedMatrix<T>::at(typename vector<T>::size_type y, typename vector<T>::size_type x) {
    if (x < 0 || x >= ml + mr) {
        ostringstream errMsg;
        errMsg << "The argument is out of range ((" << y << ", " << x << ") is called for [" << n << "x" << ml << "|" << n << "x" << mr << "] augmented matrix\n";
        throw out_of_range(errMsg.str());
    }
    if (x < ml) return matl.at(y, x);
    else return matr.at(y, x - ml);
}

template <class T>
const T& AugmentedMatrix<T>::at(typename vector<T>::size_type y, typename vector<T>::size_type x) const {
    if (x < 0 || x >= ml + mr) {
        ostringstream errMsg;
        errMsg << "The argument is out of range ((" << y << ", " << x << ") is called for [" << n << "x" << ml << "|" << n << "x" << mr << "] augmented matrix\n";
        throw out_of_range(errMsg.str());
    }
    if (x < ml) return matl.at(y, x);
    else return matr.at(y, x - ml);
}

template <class T>
Matrix<T> AugmentedMatrix<T>::left() const {
    return matl;
}

template <class T>
Matrix<T> AugmentedMatrix<T>::right() const {
    return matr;
}

template <class T>
void AugmentedMatrix<T>::resize(typename vector<T>::size_type nn, typename vector<T>::size_type mml, typename vector<T>::size_type mmr) {
    matl = Matrix<T>(nn, mml);
    matr = Matrix<T>(nn, mmr);
    n = nn;
    ml = mml;
    mr = mmr;
}

template <class T>
bool AugmentedMatrix<T>::operator==(const AugmentedMatrix& p) const {
    return (matl == p.matl && matr == p.matr);
}

template <class T>
bool AugmentedMatrix<T>::operator!=(const AugmentedMatrix& p) const {
    return !(*this == p);
}

template <class T>
AugmentedMatrix<T> AugmentedMatrix<T>::gauss() const {
    AugmentedMatrix<T> temp(*this);
    typename vector<T>::size_type y = 0, x = 0;
    while (y < n && x < ml) {
        typename vector<T>::size_type mPos = 0;
        T mVal = 0;
        for (typename vector<T>::size_type i = y; i < n; ++i) if (mVal < abs(temp.at(i, x))) mPos = i, mVal = abs(temp.at(i, x));
        if (!mVal) ++x;
        else {
            for (typename vector<T>::size_type j = 0; j < ml + mr; ++j) swap(temp.at(y, j), temp.at(mPos, j));
            for (typename vector<T>::size_type i = y + 1; i < n; ++i) {
                T f = temp.at(i, x) / temp.at(y, x);
                temp.at(i, x) = 0;
                for (typename vector<T>::size_type j = x + 1; j < ml + mr; ++j) temp.at(i, j) -= temp.at(y, j) * f;
            }
            ++y, ++x;
        }
    }
    return temp;
}

template <class T>
AugmentedMatrix<T> AugmentedMatrix<T>::gauss_jordan() const {
    AugmentedMatrix<T> temp = gauss();
    vector<typename vector<T>::size_type> lPos;
    lPos.reserve(ml);
    typename vector<T>::size_type y = 0;
    for (typename vector<T>::size_type j = 0; y < n && j < ml; ++j) if (temp.at(y, j)) lPos.push_back(j), ++y;
    --y;
    for (; y >= 0 && y < n; --y) {
        typename vector<T>::size_type x = lPos.at(y);
        for (typename vector<T>::size_type j = x + 1; j < ml + mr; ++j) temp.at(y, j) /= temp.at(y, x);
        temp.at(y, x) = 1;
        for (typename vector<T>::size_type i = 0; i < y; ++i) {
            for (typename vector<T>::size_type j = x + 1; j < ml + mr; ++j) temp.at(i, j) -= temp.at(y, j) * temp.at(i, x);
            temp.at(i, x) = 0;
        }
    }
    return temp;
}

template class AugmentedMatrix<short>;
// template class AugmentedMatrix<unsigned short>;
template class AugmentedMatrix<int>;
// template class AugmentedMatrix<unsigned int>;
template class AugmentedMatrix<long>;
// template class AugmentedMatrix<unsigned long>;
template class AugmentedMatrix<long long>;
// template class AugmentedMatrix<unsigned long long>;
template class AugmentedMatrix<float>;
template class AugmentedMatrix<double>;
template class AugmentedMatrix<long double>;
