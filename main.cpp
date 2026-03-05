#include <iostream>
#include "Matrix.hpp"
#include "MatrixAlgorithm.hpp"

using namespace std;
using namespace algorithms;

int main() {
    try {
        //Matrix Olusturma
        cout << "Create Matrix" << endl;
        Matrix<int> matrix_int(3, 3, 7);
        Matrix<double> matrix_double(4, 4, 5.5);
        cout << "Int Matrix (3x3):\n" << matrix_int << endl;
        cout << "Double Matrix (4x4):\n" << matrix_double << endl;

        //Copy/Move
        cout << "Copy and Move" << endl;
        Matrix<double> A(2, 2, 1.0);
        A(0, 1) = 2.0;
        Matrix<double> B = A; //Copy Constructor
        Matrix<double> C = std::move(Matrix<double>(2, 2, 3.0)); //Move Constructor
        cout << "Matrix A:\n" << A;
        cout << "Matrix B (Copy matrix of A):\n" << B;
        
        B(0, 0) = 37.0;
        A = B; // Copy Assignment
        cout << "Matrix A after assignnmentt:\n" << A << endl;

        //Arithmetic operations
        cout << "Arithmetic Operators" << endl;
        Matrix<double> sayi1(2, 2, 8.0);
        Matrix<double> sayi2(2, 2, 3.0);
        cout << "Addition(sayı1 + sayı2):\n" << (sayi1 + sayi2);
        cout << "Subtraction(sayı1 - sayı2):\n" << (sayi1 - sayi2);
        cout << "Unary(-)(-sayı1):\n" << (-sayi1);
        
        sayi1 += sayi2; //+=
        cout << "sayı1 += sayı2:\n" << sayi1 << endl;

        //Skaler İşlemler
        cout << "Scalar Operations" << endl;
        Matrix<double> scalar(3, 1, 6.0);
        cout << "Multiplication(scalar * 5):\n" << (scalar * 5.0);
        cout << "Friend Function Multiplication(10 * scalar):\n" << (10.0 * scalar); //scalar * A işlemi için
        cout << "Division (scalar / 2):\n" << (scalar / 2.0) << endl;

        //Matris Çarpımı
        cout << "Matrix Multiplication" << endl;
        Matrix<double> carpan1(2, 3, 0.0); // 2x3
        carpan1(0, 0) = 1; carpan1(0, 1) = 2; carpan1(0, 2) = 3;
        carpan1(1, 0) = 4; carpan1(1, 1) = 5; carpan1(1, 2) = 6;

        Matrix<double> carpan2(3, 2, 0.0); // 3x2
        carpan2(0, 0) = 7;  carpan2(0, 1) = 8;
        carpan2(1, 0) = 9;  carpan2(1, 1) = 10;
        carpan2(2, 0) = 11; carpan2(2, 1) = 12;

        cout << "[2x3] * [3x2] = :\n" << (carpan1 * carpan2) << endl;

        //Matrix Algoritmaları (Transpose, Identity, Determinant, Inverse, Pow)
        cout << "Advanced Algorithms" << endl;
        Matrix<double> matrix_for_algs(2, 2, 0.0);
        matrix_for_algs(0, 0) = 4; matrix_for_algs(0, 1) = 7;
        matrix_for_algs(1, 0) = 2; matrix_for_algs(1, 1) = 6;

        cout << "Initial Matrix:\n" << matrix_for_algs;
        cout << "Transposed Matrix:\n" << transpose(matrix_for_algs);
        cout << "Identity Matrix(3x3):\n" << identity<double>(3);
        cout << "Determinant of Matrix: " << det(matrix_for_algs) << endl;

        Matrix<double> inverse_matrix = inverse(matrix_for_algs);
        cout << "Inverse Matrix:\n" << inverse_matrix;
        cout << "Verification with A*A^-1 :\n" << (matrix_for_algs * inverse_matrix) << endl;

        //Power
        cout << "Power" << endl;
        Matrix<double> P(2, 2, 1.0);
        P(0, 1) = 2.0; 
        cout << "Matrix P:\n" << P;

        //pow fonksiyonu ile hesaplama
        Matrix<double> power_matrix = pow(P, 3);
        cout << "Result from pow(P, 3):\n" << power_matrix;

        //Manuel doğrulama
        cout << "Result from manual (P * P * P):\n";
        Matrix<double> matrix_power_by_manual = P * P * P;
        cout << matrix_power_by_manual << endl;

        //Karşılaştırma
        if (power_matrix == matrix_power_by_manual) {
            cout << "They are equal!" << endl;
        } else {
            cout << "They are different!" << endl;
        }

        //Hata Senaryoları
        cout << "Error Hanndling Scenarioss" << endl;
        
        //size_mismatch
        try {
            Matrix<double> e1(1, 5, 1);
            Matrix<double> e2(3, 4, 1);
            cout << "Testing size mismatch addition:" << endl;
            Matrix<double> err = e1 + e2;
        } catch (const invalid_argument& e) {
            cout << "Caught Expected Error: " << e.what() << endl;
        }

        //out_of_range
        try {
            cout << "Testing out of bounds access:" << endl;
            matrix_int(6, 9) = 100;
        } catch (const out_of_range& e) {
            cout << "Caught Expected Error: " << e.what() << endl;
        }

        //runtime_error
        try {
            Matrix<double> singular(3, 3, 1.0); // Tüm elemanları 1 olan matrisin det=0
            cout << "Testing inverse of singular matrix..." << endl;
            Matrix<double> err = inverse(singular);
        } catch (const runtime_error& e) {
            cout << "Caught Expected Error: " << e.what() << endl;
        }

    } catch (const exception& e) {
        cerr << "Error but unexpected!: " << endl;
    }

    cout << "THE END" << endl;
    return 0;
}