MATRIX OPERATIONS AND ALGORITHMS LIBRARY:

This library is a C++ project which includes matrix operations. It created with SOLID principles, error handling and mathematical correctness. It gives me permission with various numeric types to use in mathematical operatios.


1. STRUCTURE OF PROJECT:

Matrix.hpp --> Core of the project. It includes fundamenntal operations("+", "-", "*", "/", etc.) and properties of a Matrix class.

MatrixAlgorithms.hpp --> It includes advanced methods(Determinant, Inverse, Power...) in it.

main.cpp --> Test file to demonstrate error handling and matrix operations.


2. SOLID PRINCIPPLES IN PROJECT:

Single Responsibility Principle: The Matrix class(Matrix.hpp) handles only data storage and basic operators. All operator overloading methods, constructors and private data are inside of Matrix.hpp class.(Complex methods are not inncluded.)

Open/Closed Principle (OCP): New mathematical operations can be added to the algorithms namespace later.

Liskov Substitution Principle (LSP): I used composition instead of inheritance from std::vector because it is safer and protects my data better. For the Liskov Substitution Principle, I chose this way to avoid the risks of using standard containers as base classes. To get correct results, I used Gaussian elimination with partial pivoting for calculating determinants and inverse matrices.

Interface Segregation Principle (ISP): Mathematical logic is kept separate from I/O formatting and advanced algorithms. With this way, users use only the modules that they need. It is easier and more effficient to use it like this.

Dependency Inversion Principle (DIP): Advanced algorithms can't interact with the Matrix.hpp private features, it can only reach the public part. (rows(), cols()...)


3. Design Desicions:

Complex Algorithms Implementation:

a)  Determinant Calculation:
    To find the determinant of a square matrix , I used Gaussian Elimination with Partial Pivoting:
-   Pivoting Strategy: The algorithm looks for the largest abs. value in the current column (which is the pivot) and swaps rows. This is very important to avoid dividing by zero and to keep the results right.
-   Upper Triangular Form: I change the matrix into an upper triangular form where all elements below the diagonal are zero.
-   Swapping Effect: The determinant is the product of all diagonal elements. If rows are swapped an odd number of times, the result is multiplied by -1.

b)  Matrix Inverse:
    I implemented the inverse() function for square matrices using the Gauss-Jordan Elimination method:
-   Augmented Matrix: I conceptually work with an identity matrix alongside our original matrix.
-   Normalization: I divide each row by its pivot element to make the diagonal values equal to 1.
-   Elimination: I use row operations to make all other elements in the column zero. In the end, our initial matrix becomes an identity matrix, and our identity matrix becomes the inverse.
-   Failure Check: If it's determinant equals to zero, then it will throw an error (runtime_error).

c)  Power (Exponentiation):
    The pow function calculates A^n for non-negative integers:
-   Loop Method: I multiply the matrix by itself n times in a loop.
-   Zero Power: If n is 0, the function returns an Identity Matrix(For A^n, when n is zero, it is equal to Identity)
-   Checkng: The code checks if the matrix is square and if n is not negative.

d)  Numerical Stability (Epsilon):
    Computers may have some issues when working with double types. To fix it:
-   Epsilon Policy: I use a very small number called epsilon_value(epsilon_coeff) (1×10^−9 for determinant and 1×10^−15 for inverse).
-   Safe Comparison: Instead of checking if a number is exactly 0, I check if its abs value is smaller than epsilon(better opperator== check).

e) Errors:
-   std::invalid_argument --> for dimension mismatches
-   std::out_of_range --> for bounds checking in operator()
-   std::runtime_error --> for singular matrices or non-invertible cases


4. How to Run:

a) Open your terminal in directory
b) Compile the test suite(main.cpp) using g++
c) g++ -g main.cpp -o main.exe                      //write this
d) ./main.exe                                       //write this to run main.exe



                                                                    SALİH BARKIN AKKAYA 202211004

