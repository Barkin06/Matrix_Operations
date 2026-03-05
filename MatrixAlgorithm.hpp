#ifndef MATRIX_ALGORITHMS_HPP
#define MATRIX_ALGORITHMS_HPP

#include "Matrix.hpp"
#include <cmath>
#include <vector>
#include <stdexcept>

using std::abs;

namespace algorithms {

    // https://en.wikipedia.org/wiki/Identity_matrix
    template <typename T>
    Matrix<T> identity(size_t n) { //int type değil, negatif verilsin istemem
        Matrix<T> result(n, n, T(0));
        for (size_t i = 0; i < n; i++) {
            result(i, i) = T(1);
        }
        return result;
    }

    // https://en.wikipedia.org/wiki/Transpose
    template <typename T>
    Matrix<T> transpose(const Matrix<T>& other) {
        Matrix<T> result(other.cols(), other.rows(), T(0));
        for (int i = 0; i < other.rows(); i++) {
            for (int j = 0; j < other.cols(); j++) {
                result(j, i) = other(i, j); //ilk matrisin sütunu diğerinin satırına, diğerinin sütunu ilk matrisin satırına eşit
            }
        }
        return result;
    }

    template <typename T>
    Matrix<T> pow(const Matrix<T>& matrix, int n) {
        if (matrix.rows() != matrix.cols()) {
            throw std::invalid_argument("It is not a square matrix!");
        }
        if (n < 0) {
            throw std::invalid_argument("Power can't be a negative value!");
        }
        if (n == 0) {
            return identity<T>(matrix.rows());
        }

        // Fast Power mantığını pek kuramadım...
        Matrix<T> result = identity<T>(matrix.rows());
        for (int i = 0; i < n; i++) {
            result = result * matrix;
        }

        return result;
    }

    template <typename T>
    T det(const Matrix<T>& matrix){
        if(matrix.rows() != matrix.cols()){
            throw std::invalid_argument("Determinant is for square matrices!");
        }

        size_t n = matrix.rows(); //negatif değer istemiyoruz

        if (n == 1) { //tek boyutlu matris ise (0,0) değerini return et(tek o değer var determinant o da)
            return matrix(0, 0);
        }
        // kopya matrix
        Matrix<T> dummy = matrix; 
        T determinant = 1;
        T epsilon_value = 1e-9;
        
        for (int i = 0; i < n; i++) {
            //mutlak değeri en büyük elemanı bulup satır i'ye taşı
            int pivot = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(dummy(j, i)) > abs(dummy(pivot, i))) {
                    pivot = j;
                }
            }
            // hassasiyet (eppsilon) kontrolü
            if (abs(dummy(pivot, i)) < epsilon_value) {
                return 0;
            }

            if (pivot != i) {
                for (int k = 0; k < n; k++) {
                    std::swap(dummy(i, k), dummy(pivot, k)); //pivot ile o anki satırı değiştir (pivot büyük)
                }
                determinant = determinant * -1; //satırlar değişirse det * -1
            }

            for (int j = i + 1; j < n; j++) { // upper trianngular forma getirir
                T x = dummy(j, i) / dummy(i, i);
                for (int k = i + 1; k < n; k++) {
                    dummy(j, k) = dummy(j,k) - x * dummy(i, k);
                }
            }
            
            determinant = determinant * dummy(i, i);
        }

        return determinant;
    }

    template <typename T>
    Matrix<T> inverse(const Matrix<T>& matrix) {
        if (matrix.rows() != matrix.cols()) {
            throw std::invalid_argument("Only a square matrix has an inverse matrix!");
        }

        // kopya matrix
        int n = matrix.rows();
        Matrix<T> A = matrix;
        Matrix<T> I = identity<T>(n);
        T epsilon = 1e-15;

        //pivot secimi
        for (int col = 0; col < n; col++) {
            int pivot = col;
            for (int r = col + 1; r < n; r++) {
                if (abs(A(r, col)) > abs(A(pivot, col))) {
                    pivot = r;
                }
            }
            //det. kontrolu
            if (abs(A(pivot, col)) < epsilon) {
                throw std::runtime_error("Matrix has zero determinant(no inverse)!");
            }
        
            if (pivot != col) {
                for (int k = 0; k < n; k++) {
                    std::swap(A(col, k), A(pivot, k));
                    std::swap(I(col, k), I(pivot, k));
                }
            }

            T div = A(col, col);
            for (int j = 0; j < n; j++) {
                A(col, j) = A(col, j) / div;
                I(col, j) = I(col, j) / div;
            }

            for (int r = 0; r < n; r++) {
                if (r == col){
                    continue;
                }

                T x = A(r, col);
                for (int c = 0; c < n; c++) {
                    A(r, c) = A(r, c) - x * A(col, c);
                    I(r, c) = I(r, c) - x * I(col, c);
                }
            }
        }

        return I;
    }
}

#endif