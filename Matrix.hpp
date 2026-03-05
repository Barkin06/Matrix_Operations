#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <cmath>

//using namespace std; --> kütüphane yazarken olumsuz etkilemesini istemem

using std::vector;
using std::move;
using std::invalid_argument;
using std::runtime_error;
using std::out_of_range;
using std::ostream;



template <typename T>
class Matrix{
    private:

        size_t _rows; //negatif değer almasın
        size_t _cols;
        vector <T> _data;

    public:

        Matrix() : _rows(0), _cols(0), _data(0) {} //Default Constructor --> 0x0 matrix

        Matrix(size_t row, size_t col, T initial_val){ //negatif değer almasın 
            this->_rows = row;
            this->_cols = col;
            this->_data.assign(row*col, initial_val); //Assignn ile atadim.
        }

        Matrix(const Matrix& other){  //Copy Constructor
            this->_cols = other._cols;
            this->_rows = other._rows;
            this->_data = other._data;
        }

        Matrix(Matrix&& other){  //Move Constructor
            this->_rows = other._rows;
            this->_cols = other._cols;
            this->_data = move(other._data);

            other._rows = 0;
            other._cols = 0;
        }
        ~Matrix() = default;

        int rows() const{
            return this->_rows;
        }

        int cols() const{
            return this->_cols;
        }

        vector <T> &data() const{
            return _data;
        }

        Matrix& operator=(Matrix& other) { //copy assign op. overloading
            if (this != &other) { //self assign için
                this->_rows = other._rows;
                this->_cols = other._cols;
                this->_data = other._data;
            }
            return *this;
        }

        Matrix& operator=(Matrix&& other) {  //move assign op overloading
            if (this != &other) {
                this->_rows = other._rows;
                this->_cols = other._cols;
                this->_data = move(other._data);
                
                other._rows = 0;
                other._cols = 0;
            }
            return *this;
        }

        Matrix operator+() const { // unary+
            return *this;
        }

        Matrix operator-() const { //unary-
            Matrix <T> result(this->_rows, this->_cols,T());
            for(int i = 0 ; i < this->_cols * this->_rows ; i++){
                result._data[i] = -this->_data[i];
            }

            return result;
        }

        Matrix operator+(const Matrix &other) const{ // + overrload
            if(this->_rows != other._rows || this->_cols != other._cols){
                throw invalid_argument("Matrix sizes are not matched for addition!");
            }

            Matrix <T> result(this->_rows, this->_cols,T());

            for(int i = 0; i < other._rows * other._cols; i++){
                result._data[i] = this->_data[i]+other._data[i];
            }

            return result;
        }

        Matrix& operator+=(const Matrix&other){ // += overload
            if(this->_rows != other._rows || this->_cols != other._cols){
                throw invalid_argument("Matrix sizes are not matched for addition!");
            }

            for(int i = 0; i < this->_rows * this->_cols; i++){
                this->_data[i] = this->_data[i] + other._data[i];
            }

            return *this;

        }

        Matrix operator-(const Matrix &other) const { // - overload
            if (this->_rows != other._rows || this->_cols != other._cols) {
                throw std::invalid_argument("Matrix sizes are not matched for subtraction!");
            }

            Matrix<T> result(this->_rows, this->_cols , T());

            for (int i = 0; i < this->_data.size(); i++) {
                result._data[i] = this->_data[i] - other._data[i];
            }

            return result;
        }

        Matrix& operator-=(const Matrix&other){ // -= overload
            if(this->_rows != other._rows || this->_cols != other._cols){
                throw invalid_argument("Matrix sizes are not matched for subtraction!");
            }

            for(int i = 0; i < this->_rows * this->_cols; i++){
                this->_data[i] = this->_data[i] - other._data[i];
            }

            return *this;
            
        }


        Matrix operator*(const T& scalar_coeff) const { // * overload scalar coefficient
            Matrix<T> result(this->_rows, this->_cols, T());

            for (int i = 0; i < this->_data.size(); i++) {
                result._data[i] = this->_data[i] * scalar_coeff;
            }

            return result;
        }

        friend Matrix operator*(const T& scalar, const Matrix& mat) { //aynı çarpma metodunu kullanabiliriz 
            return mat * scalar;
        }

        Matrix operator*(const Matrix& other) const {  // A*B matrix çarpımı
        if (this->_cols != other._rows) {
            throw std::invalid_argument("Matrix multiplication is not possible!");
        } 

        Matrix<T> result(this->_rows, other._cols, T());
        
        for (int i = 0; i < this->_rows; i++) {
            for (int j = 0; j < other._cols; j++) {
                for (int k = 0; k < this->_cols; k++) {
                    //index = satır * genişlik + sütun formülü ile 1D bir array gibi düşünmeye çalıştım.
                    result._data[i * other._cols + j] = result._data[i * other._cols + j] + (this->_data[i * this->_cols + k] * other._data[k * other._cols + j]);    
                }
            }
        }

        return result;
    }

        Matrix& operator*=(const Matrix& other) { // *= overload the matrix mult with assignment
            if (this->_cols != other._rows) {
                throw invalid_argument("Matrix multipication is not possible!(dimensions are incompatible)");
            }

            Matrix<T> result(this->_rows, other._cols, T()); // this datasını for döngüleri bitmeden değiştiremem. Ekstra matrixe ihtiyacım var.
           
           //index = satır * genişlik + sütun formülü ile 1D bir array gibi düşünmeye çalıştım.
           for (int i = 0; i < this->_rows; i++) {
                for (int j = 0; j < other._cols; j++) {
                    for (int k = 0; k < this->_cols; k++) {
                        result._data[i * other._cols + j] = result._data[i * other._cols + j] + (this->_data[i * this->_cols + k] * other._data[k * other._cols + j]);
                    }
                }
            }

            *this = result;
            return *this;

        }

        Matrix& operator*=(const T& scalar_coeff) { // *= overload
            for (int i = 0; i < this->_data.size(); i++) {
                this->_data[i] = this->_data[i] * scalar_coeff;
            }

            return *this;
        }

        Matrix operator/(const T& scalar_coeff) const { // / overload

            if (scalar_coeff == T(0)) {
                throw runtime_error("Division by zero is not allowed!");
            }

            Matrix<T> result(this->_rows, this->_cols, T());

            for (int i = 0; i < this->_data.size(); i++) {
                result._data[i] = this->_data[i] / scalar_coeff;
            }

            return result;
        }

        Matrix& operator/=(const T& scalar_coeff) { // /= overload
            if (scalar_coeff == T(0)) {
                throw runtime_error("Division by zero is not allowed!");
            }

            for (int i = 0; i < this->_data.size(); i++) {
                this->_data[i] = this->_data[i] / scalar_coeff;
            }

            return *this;
        }

        bool operator==(const Matrix& other) const{ //== overlooad
            if (this->_rows != other._rows || this->_cols != other._cols) {
                return false;
            }

            // https://www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast/
            // https://floating-point-gui.de/
            const T epsilon_value = static_cast<T>(1e-9);
            

            for(int i = 0 ; i < this->_rows * this->_cols ; i++){
                if (abs(this->_data[i] - other._data[i]) > epsilon_value) {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const Matrix& other) const{ //!= overload
            if(*this==other){
                return false;
            }

            return true;
        }

        T& operator()(size_t row, size_t col) { // Read ve write için (negatif olmmasın diye size_t)
            if (this->_rows <= row || this->_cols <= col) {
                throw out_of_range("Index of matrix is out of bounds!");
            }

            return this->_data[(row * this->_cols) + col];  // n inci satırdaki m inci eleman ve onun col kadar eklenmiş hali
        }

        const T& operator()(size_t row, size_t col) const {
            if (row >= static_cast<size_t>(_rows) || col >= static_cast<size_t>(_cols)) {
                throw out_of_range("Index out of bounds!");
            }
            return _data[row * _cols + col];
        }

        friend ostream& operator<<(ostream &os, const Matrix <T>& other){
            for(int i = 0 ; i < other._rows; i++){
                for(int j = 0 ; j < other._cols; j++){
                    os << other(i,j) << "\t";
                }
                os << "\n";
            }

            return os; 
        }


        //MatrixAlgorithm.hpp için olan kısım:

};
#endif