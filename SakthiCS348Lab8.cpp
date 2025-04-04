/* Okay , so this is CS 348 Lab 8and this is the Code on Visual Studio that will 
... oversee the numbers in the graph and will print question 1-7 that are on canvas
the program will take the file nums.txt and the produce the output which in on canvas
And The file name is SakthiLab8 
 ... And Finally ... 
Name ... Sakthi Sivasubramanian 
First Created ... April 3
Final Edits ... April 3
*/ 
#include <iostream> // This IS including the input/output stream library
#include <fstream> // This IS including the file input/output library
#include <vector> // this is including the vector container from the standard library
#include <iomanip> // this is including the library for output formatting

using namespace std; // this is using the standard 

vector<vector<int>> getTheNums(ifstream& file , int N) { // this is the function to read values from file
    vector<vector<int>> matrix(N , vector<int>(N)); // this is creating a 2d vector of size N x N
    for (int i = 0 ; i < N ; ++i) // this is looping through the rows
        for (int j = 0 ; j < N ; ++j) // this is looping through the columns
            file >> matrix[i][j] ; // this is reading every number into the graph
    return matrix ; // this is returning the completed graph
}

void printTheNums(const vector<vector<int>>& matrix) { // this is the function to print a matrix
    for (const auto& row : matrix) { // this is looping through each row
        for (int val : row) // this is looping through each value in the row
            cout << setw(4) << val ; // this is printing the value with spacing
        cout << endl ; // this is printing a newline after each row
    }
}

vector<vector<int>> addNums(const vector<vector<int>>& A , const vector<vector<int>>& B) { // this is a function to add the two numbers
    int N = A.size() ; // this is getting the size
    vector<vector<int>> result(N , vector<int>(N)) ; // this is initializing the result 
    for (int i = 0 ; i < N ; ++i) // this is looping through the rows
        for (int j = 0 ; j < N ; ++j) // this is looping through the columns
            result[i][j] = A[i][j] + B[i][j] ; // this is adding corresponding nums
    return result ; // this is returning the result matrix
}

vector<vector<int>> NumsProduct(const vector<vector<int>>& A , const vector<vector<int>>& B) { // this is a function to multiply two matrices
    int N = A.size() ; // this is getting the size
    vector<vector<int>> result(N, vector<int>(N)) ; // this is initializing the result 
    for (int i = 0 ; i < N ; ++i) // this is looping through rows
        for (int j = 0 ; j < N ; ++j) // this is looping through columns
            for (int k = 0 ; k < N ; ++k) // this is performing inner multiplication
                result[i][j] += A[i][k] * B[k][j] ; // this is adding the product of corresponding elements
    return result ; // this is returning the multiplied matrix
}

int SumDiago(const vector<vector<int>>& matrix) { // this is the function to sum main and secondary diagonals
    int N = matrix.size() , sum = 0; // this is initializing matrix size and sum
    for (int i = 0 ; i < N ; ++i) { // this is looping through the diagonal indices
        sum += matrix[i][i] ; // this is adding the main diagonal element
        if (i != N - 1 - i) // this is checking if it's not the center element (to avoid double counting)
            sum += matrix[i][N - 1 - i] ; // this is adding the secondary diagonal element
    }
    return sum ; // this is returning the total sum
}

void swapRows(vector<vector<int>>& matrix , int r1 , int r2) { // this is the function to swap two rows
    if (r1 >= 0 && r2 >= 0 && r1 < matrix.size() && r2 < matrix.size()) // this is checking if indices are valid
        swap(matrix[r1] , matrix[r2]); // this is swapping the rows
}

void swapCols(vector<vector<int>>& matrix , int c1 , int c2) { // this is the function to swap two columns
    if (c1 >= 0 && c2 >= 0 && c1 < matrix[0].size() && c2 < matrix[0].size()) // this is checking if indices are valid
        for (auto& row : matrix) // this is iterating through each row
            swap(row[c1] , row[c2]) ; // this is swapping the columns
}

void updateTheMatr(vector<vector<int>>& matrix , int r , int c , int val) { // this is the function to update a matrix cell
    if (r >= 0 && c >= 0 && r < matrix.size() && c < matrix[0].size()) // this is checking if the indices are valid
        matrix[r][c] = val ; // this is updating the value
}

int main() { // this is the start of the main function
    string filename; // this is the filename variable
    cout << "Please Type the file ... "; // this is prompting user for file name
    cin >> filename; // this is reading the file name
    ifstream file(filename); // this is opening the file
    if (!file) return 1; // this is checking if file fails to open

    int N; // this is the matrix size
    file >> N; // this is reading the size from the file
    vector<vector<int>> A = getTheNums(file , N); // this is reading matrix A
    vector<vector<int>> B = getTheNums(file , N); // this is reading matrix B
    vector<vector<int>> TheOriginalA = A; // this is saving a copy of matrix A
    vector<vector<int>> TheOriginalB = B; // this is saving a copy of matrix B

    cout << "question 1 ... "; // this is marking question 1
    cout << "Matrix A:\n"; // this is showing matrix A
    printTheNums(A); // this is printing matrix A
    cout << "Matrix B:\n"; // this is showing matrix B
    printTheNums(B); // this is printing matrix B

    cout << "question 2 ..."; // this is marking question 2
    cout << "A + B:\n"; // this is showing matrix addition
    printTheNums(addNums(A , B)); // this is printing the result of A + B

    cout << "question 3 ..."; // this is marking question 3
    cout << "A * B:\n"; // this is showing matrix multiplication
    printTheNums(NumsProduct(A , B)); // this is printing the result of A * B

    cout << "question 4 ..."; // this is marking question 4
    int diagA = SumDiago(A); // this is summing diagonals of A
    int diagB = SumDiago(B); // this is summing diagonals of B
    int diagTotal = diagA + diagB; // this is computing the total sum

    cout << "The Sum of the diagonals of Ais ... " << diagA << endl; // this is printing sum of A diagonals
    cout << "The Sum of the diagonals of Bis " << diagB << endl; // this is printing sum of B diagonals
    cout << "The Combined Sum of the diagonals for A and B is ... " << diagTotal << endl; // this is printing total

    cout << "question 5 ..."; // this is marking question 5
    char matrixChoiceQ5; // this is the variable for matrix choice in question 5
    int row1 , row2; // this is declaring row index variables
    cin.ignore(numeric_limits<streamsize>::max() , '\n'); // this is clearing leftover input

    cout << " which matrix would you like to swap rows in? (A or B): "; // this is prompting for matrix choice
    cin >> matrixChoiceQ5; // this is reading the matrix choice

    cout << "Please Type two row indices to swap (0 to " << N - 1 << ") And if you want to swap 1 and 2 ... type 1 2 "; // this is prompting for row indices
    cin >> row1 >> row2; // this is reading the row indices

    if (cin.fail() || row1 < 0 || row1 >= N || row2 < 0 || row2 >= N) { // this is checking for invalid indices
        cout << "The Rows indices are invalid . They must be between 0 and " << N - 1 << "." << endl; // this is printing an error
    } else if (matrixChoiceQ5 == 'A' || matrixChoiceQ5 == 'a') { // this is checking if user chose matrix A
        vector<vector<int>> Acopy = TheOriginalA; // this is copying matrix A
        swapRows(Acopy, row1, row2); // this is swapping the rows in A
        cout << "Matrix A after swapping rows " << row1 << " and " << row2 << ":\n"; // this is printing result
        printTheNums(Acopy); // this is printing matrix A
    } else if (matrixChoiceQ5 == 'B' || matrixChoiceQ5 == 'b') { // this is checking if user chose matrix B
        vector<vector<int>> Bcopy = TheOriginalB; // this is copying matrix B
        swapRows(Bcopy, row1, row2); // this is swapping the rows in B
        cout << "Matrix B after swapping rows " << row1 << " and " << row2 << ":\n"; // this is printing result
        printTheNums(Bcopy); // this is printing matrix B
    } else {
        cout << "The Rows indicies aare invalid because they should be between 0 and " << N - 1 << "." << endl; // this is printing invalid matrix choice
    }

    cout << "question 6 ..."; // this is marking question 6
    int col1 , col2; // this is declaring column index variables
    cout << "Please Type two column indices to swap (0 to " << N - 1 << ") And if you want to swap 1 and 2 ... type 1 2 "; // this is prompting for column indices
    cin >> col1 >> col2; // this is reading the column indices
    if (col1 >= 0 && col1 < N && col2 >= 0 && col2 < N) { // this is validating column indices
        vector<vector<int>> Acopy = TheOriginalA; // this is copying matrix A
        vector<vector<int>> Bcopy = TheOriginalB; // this is copying matrix B
        swapCols(Acopy , col1 , col2); // this is swapping columns in A
        cout << "Matrix A after swapping columns " << col1 << " and " << col2 << ":\n"; // this is printing A result
        printTheNums(Acopy); // this is printing matrix A

        swapCols(Bcopy , col1 , col2); // this is swapping columns in B
        cout << "Matrix B after swapping columns " << col1 << " and " << col2 << ":\n"; // this is printing B result
        printTheNums(Bcopy); // this is printing matrix B
    } else {
        cout << "The Column indicies aare invalid because they should be between 0 and " << N - 1 << "." << endl; // this is printing error
    }

    cout << "question 7 ..."; // this is marking question 7
    if (cin.fail())  { // this is checking if previous input failed
        cin.clear(); // this is clearing error state
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this is flushing input buffer

    char matrixChoiceQ7; // this is declaring matrix choice for question 7
    int row , col , newVal; // this is declaring update input variables

    cout << "Which matrix would you like to update? (A or B): "; // this is prompting user
    cin >> matrixChoiceQ7; // this is reading user input

    cout << "Please Type row index (0 to " << N - 1 << "): "; // this is prompting for row
    cin >> row; // this is reading row index

    cout << "Please Type column index (0 to " << N - 1 << "): "; // this is prompting for column
    cin >> col; // this is reading column index

    cout << "Please Type the new value you would want to change tooo ... : "; // this is prompting for new value
    cin >> newVal; // this is reading new value

    if (cin.fail() || row < 0 || row >= N || col < 0 || col >= N) { // this is validating input
        cout << "The row / column you entered is invalid ." << endl; // this is printing error
    } else if (matrixChoiceQ7 == 'A' || matrixChoiceQ7 == 'a') { // this is checking if matrix is A
        vector<vector<int>> Acopy = TheOriginalA; // this is copying A
        updateTheMatr(Acopy , row , col , newVal); // this is updating A
        cout << "Matrix A after update:\n"; // this is showing result
        printTheNums(Acopy); // this is printing updated matrix A
    } else if (matrixChoiceQ7 == 'B' || matrixChoiceQ7 == 'b') { // this is checking if matrix is B
        vector<vector<int>> Bcopy = TheOriginalB; // this is copying B
        updateTheMatr(Bcopy , row , col , newVal); // this is updating B
        cout << "Matrix B after update:\n"; // this is showing result
        printTheNums(Bcopy); // this is printing updated matrix B
    } else {
        cout << "The Matrix you chose is invalid . please type A or B." << endl; // this is printing invalid choice
    }

    return 0; // this is ending the main function
}
// And This is the last line !!! 