/* Okay , so this is CS 348 Lab 9 and this is the Code on Visual Studio that will 
... Get The Answers to the + * and swapping numbers in the graph 
the program will take the file .txt (with nums) and the produce the output which says which is the answer 
should print the answer which is another number graph ... And Finally ... 
Name ... Sakthi Sivasubramanian 
First Created ... April 6th
Final Edits ... April 9th 
*/ 
#include <iostream> // this is including the input and output stream library
#include <fstream> // this is including the file input and output library
#include <iomanip> // this is including the library to control the output format
#include <vector> // this is including the vector container from the standard library
#include <string> // this is including the string library
using namespace std ; // this is using the standard namespace

template <typename T> // this is declaring a template class to handle both int and double
class NumFunctionSolvers { // this is the class
    int size ; // this is the size of the ...
    vector<vector<T> > data; // this is a 2d vector to store matrix data

public:
NumFunctionSolvers(int n) : size(n)  , data(n , vector<T>(n)) {} // this is the constructor that initializes the matrix

    void load(ifstream& in) { // this is a function to load data from the input file
        for (int i = 0 ; i < size ; ++i) // this is looping over the rows
            for (int j = 0 ; j < size ; ++j) // this is looping over the columns
                in >> data[i][j]; // this is reading the value into the matrix
    }

    void print() const { // this is a function to print the matrix
        for (const auto& row : data) { // this is iterating through each row
            for (const auto& val : row) // this is iterating through each value in the row
                cout << setw(6) << static_cast<double>(val) ; // this is printing the value with spacing
            cout << endl ; // this is printing a newline after each row
        }
    }

    NumFunctionSolvers<T> operator+(const NumFunctionSolvers<T>& other) const { // this is overloading the + operator to add matrices
        NumFunctionSolvers<T> result(size) ; // this is initializing the result matrix
        for (int i = 0 ; i < size ; ++i) // this is iterating over rows
            for (int j = 0 ; j < size ; ++j) // this is iterating over columns
                result.data[i][j] = data[i][j] + other.data[i][j] ; // this is performing element-wise addition
        return result ; // this is returning the result matrix
    }

    NumFunctionSolvers<T> operator*(const NumFunctionSolvers<T>& other) const { // this is overloading the * operator to multiply matrices
        NumFunctionSolvers<T> result(size) ; // this is initializing the result matrix
        for (int i = 0 ; i < size ; ++i) // this is iterating over rows
            for (int j = 0 ; j < size; ++j) // this is iterating over columns
                for (int k = 0 ; k < size; ++k) // this is the inner loop for matrix multiplication
                    result.data[i][j] += data[i][k] * other.data[k][j] ; // this is computing the dot product
        return result; // this is returning the result matrix
    }

    T FunctionToSumDiagonals() const { // this is a function to sum the main and secondary diagonals
        T sum = 0; // this is initializing the sum
        for (int i = 0 ; i < size ; ++i) { // this is looping over indices
            sum += data[i][i] ; // this is adding the main diagonal element
            if (i != size - 1 - i) // this is checking for overlap on odd-sized matrices
                sum += data[i][size - 1 - i] ; // this is adding the secondary diagonal element
        }
        return sum; // this is returning the total sum
    }

    void SwapTheRows(int row1 , int row2) { // this is a function to swap two rows
        if (row1 >= 0 && row2 >= 0 && row1 < size && row2 < size) // this is checking if indices are valid
            swap(data[row1] , data[row2]) ; // this is swapping the rows
    }

    void SwapTheCols(int col1 , int col2) { // this is a function to swap two columns
        if (col1 >= 0 && col2 >= 0 && col1 < size && col2 < size) // this is checking if indices are valid
            for (int i = 0 ; i < size ; ++i) // this is iterating over each row
                swap(data[i][col1] , data[i][col2]); // this is swapping the column elements
    }

    void AddNewNumber(int r , int c , T val) { // this is a function to update a specific cell
        if (r >= 0 && r < size && c >= 0 && c < size) // this is checking if the indices are valid
            data[r][c] = val ; // this is updating the value
    }
};

int main() { // this is the start of the main function
    string NumFiles; // this is declaring a string for the filename
    cout << "Please Type the file name ... "; // this is asking the user to type the filename
    cin >> NumFiles; // this is reading the filename
    ifstream file(NumFiles); // this is opening the file using ifstream
    if (!file) return 1; // this is checking if the file opened correctly

    int N , type; // this is declaring the matrix size and type flag
    file >> N >> type; // this is reading the size and type flag

    if (type == 0) { // this is checking if the matrix is of type int
        NumFunctionSolvers<int> A(N), B(N); // this is creating two int matrices A and B
        A.load(file); // this is loading matrix A
        B.load(file); // this is loading matrix B
        NumFunctionSolvers<int> Aoriginal = A; // this is storing a copy of original A
        NumFunctionSolvers<int> Boriginal = B; // this is storing a copy of original B
        cout << "The Matrix A is ... \n"; // this is printing header for matrix A
        A.print(); // this is printing matrix A
        cout << "The Matrix B is ... \n"; // this is printing header for matrix B
        B.print(); // this is printing matrix B
        cout << "A + B is ... \n"; // this is printing header for A + B
        (A + B).print(); // this is printing A + B
        cout << "A * B is ... \n"; // this is printing header for A * B
        (A * B).print(); // this is printing A * B
        cout << "The Diagonal Sum of A is ... " << A.FunctionToSumDiagonals() << endl; // this is printing diagonal sum of A
        cout << "The Diagonal Sum if B is ... " << B.FunctionToSumDiagonals() << endl; // this is printing diagonal sum of B

        int row1 , row2 ; // this is declaring row indices to swap
        cout << "Please Type The 2 row indices to swap in A and B (starting at 0 ) ... "; // this is asking for row indices
        cin >> row1 >> row2 ; // this is reading the row indices
        A.SwapTheRows(row1 , row2); // this is swapping rows in A
        B.SwapTheRows(row1 , row2); // this is swapping rows in B
        cout << " A after swapping rows " << row1 << " and " << row2 << ":\n"; // this is printing result
        A.print(); // this is printing A
        cout << " B after swapping rows " << row1 << " and " << row2 << ":\n"; // this is printing result
        B.print(); // this is printing B

        A = Aoriginal; // this is resetting A
        B = Boriginal; // this is resetting B

        int col1 , col2 ; // this is declaring column indices to swap
        cout << "Please Type The 2 column indices to swap in A and B (starting at 0 ) ... "; // this is asking for column indices
        cin >> col1 >> col2 ; // this is reading column indices
        A.SwapTheCols(col1 , col2); // this is swapping columns in A
        B.SwapTheCols(col1 , col2); // this is swapping columns in B
        cout << "A after swapping columns " << col1 << " and " << col2 << ":\n"; // this is printing result
        A.print(); // this is printing A
        cout << "B after swapping columns " << col1 << " and " << col2 << ";\n"; // this is printing result
        B.print(); // this is printing B

        int RowThatWillBeChanged , ColumnThatWillBeChanged , NewValues ; // this is declaring update variables
        cout << "Please Type the new row number , column number , and the new value to change in A and B "; // this is asking for update input
        cin >> RowThatWillBeChanged >> ColumnThatWillBeChanged >> NewValues ; // this is reading update input
        A.AddNewNumber(RowThatWillBeChanged , ColumnThatWillBeChanged , NewValues) ; // this is updating A
        B.AddNewNumber(RowThatWillBeChanged , ColumnThatWillBeChanged , NewValues) ; // this is updating B
        cout << "A after updating (" << RowThatWillBeChanged << "," << ColumnThatWillBeChanged << ") to " << NewValues << ":\n"; // this is printing result
        A.print(); // this is printing A
        cout << "B after updating (" << RowThatWillBeChanged << "," << ColumnThatWillBeChanged << ") to " << NewValues << ":\n"; // this is printing result
        B.print(); // this is printing B

    } else { // this is if the type is double
        NumFunctionSolvers<double> A(N) , B(N); // this is creating two double matrices
        A.load(file); // this is loading matrix A
        B.load(file); // this is loading matrix B
        cout << "Matrix A:\n"; // this is printing header for A
        A.print(); // this is printing A
        cout << "Matrix B:\n"; // this is printing header for B
        B.print(); // this is printing B
        cout << "A + B:\n"; // this is printing header for A + B
        (A + B).print(); // this is printing A + B
        cout << "A * B:\n"; // this is printing header for A * B
        (A * B).print(); // this is printing A * B
        cout << "Diagonal Sum A: " << A.FunctionToSumDiagonals() << endl; // this is printing diagonal sum of A
        cout << "Diagonal Sum B: " << B.FunctionToSumDiagonals() << endl; // this is printing diagonal sum of B

        int row1 , row2 ; // this is declaring row indices
        cout << "Please Type The 2 row indices to swap in A and B (starting at 0 ) ... "; // this is asking for row indices
        cin >> row1 >> row2 ; // this is reading row indices
        A.SwapTheRows(row1 , row2); // this is swapping rows in A
        B.SwapTheRows(row1 , row2); // this is swapping rows in B
        cout << " A after swapping rows " << row1 << " and " << row2 << ":\n"; // this is printing result
        A.print(); // this is printing A
        cout << " B after swapping rows " << row1 << " and " << row2 << ":\n"; // this is printing result
        B.print(); // this is printing B

        int col1 , col2 ; // this is declaring column indices
        cout << "Please Type The 2 column indices to swap in A and B (starting at 0 ) ... "; // this is asking for column indices
        cin >> col1 >> col2 ; // this is reading column indices
        A.SwapTheCols(col1 , col2); // this is swapping columns in A
        B.SwapTheCols(col1 , col2); // this is swapping columns in B
        cout << "A after swapping columns " << col1 << " and " << col2 << ":\n"; // this is printing result
        A.print(); // this is printing A
        cout << "B after swapping columns " << col1 << " and " << col2 << ";\n"; // this is printing result
        B.print(); // this is printing B

        int RowThatWillBeChanged , ColumnThatWillBeChanged ; // this is declaring update row and column
        double NewValues ; // this is declaring new value as double
        cout << "Please Type the new row number , column number , and the new value to change in A and B "; // this is asking for update input
        cin >> RowThatWillBeChanged >> ColumnThatWillBeChanged >> NewValues ; // this is reading update input
        A.AddNewNumber(RowThatWillBeChanged , ColumnThatWillBeChanged , NewValues) ; // this is updating A
        B.AddNewNumber(RowThatWillBeChanged , ColumnThatWillBeChanged , NewValues) ; // this is updating B
        cout << "A after updating (" << RowThatWillBeChanged << "," << ColumnThatWillBeChanged << ") to " << NewValues << ":\n"; // this is printing result
        A.print(); // this is printing A
        cout << "B after updating (" << RowThatWillBeChanged << "," << ColumnThatWillBeChanged << ") to " << NewValues << ":\n"; // this is printing result
        B.print(); // this is printing B
    }
    return 0; // this is returning 0 to indicate successful execution
}
