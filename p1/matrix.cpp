/**
 * @file matrix.cpp Definitions for Matrix class methods
 *  defined in 'matrix.h'.
 *
 * @author Jacob Hansen
 * @date 3/24/16
 **/

#include"matrix.h"

using namespace std;

/**
 * Default Constructor for Matrix object.  Creates a 0x0 matrix.
 *
 * @return A Matrix object.
 */
Matrix::Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
}

/**
 * Constructor for Matrix object to build matrix from a grid of values stored
 * in a file where each line of space-separated values represents a row.
 *
 * @param fName The name of the file from which the grid will be read as a
 *        string.
 *
 * @return A Matrix object built to mimic the grid found in 'fName'.
 */
Matrix::Matrix(string fName) {
    // open file
    ifstream f;
    f.open(fName, ios::in);

    // keep track of current row and column while looping
    int r = 0;
    int c = 0;

    // loop through each line in file
    string curLine;
    int curNum;
    while(getline(f, curLine)) {
        M.resize(r+1);              // increment rows
        stringstream ss(curLine);   // read in next line

        // add each number in line to matrix
        while(ss >> curNum) {
            if(r == 0)
                ++c;

            M[r].push_back(curNum);
        }
        ++r;                       // increment rows
    }
    f.close();                     // close file

    // update member variables
    rows = r;
    cols = c;
    size = rows*cols;
}

/**
 * Constructor for Matrix object that allows user to specify the number
 * of rows and columns in the matrix.  All cell values are defaulted to 0.
 *
 * @param r The number of rows in the matrix as an integer.
 * @param c The number of columns in the matrix as an integer.
 *
 * @return A Matrix object.
 */
Matrix::Matrix(int r, int c) {
    // update dimensions
    rows = r;
    cols = c;

    M.resize(rows);             // set proper number of rows

    // resize all rows to accomodate columns
    for(int i=0; i<rows; i++)
        M[i].resize(cols);

    size = rows*cols;           // update size
}

/**
 * Set the value of a cell in the matrix.
 *
 * @param r The row of the cell as an integer.
 * @param c The column of the cell as an integer.
 * @param val The value to be placed into the cell as a long double.
 */
void Matrix::set(int r, int c, long double val) {
    M[r][c] = val;
}

/**
 * Retrieve the value stored in a certain cell within the matrix.
 *
 * @param r The row of the desired value as an integer.
 * @param c The column of the desired value as an integer.
 *
 * @return A long double representing the value stored at matrix[r, c].
 */
long double Matrix::get(int r, int c) {
    if(r >= 0 && c >= 0 && r < rows && c < cols)
        // if in matrix bounds, return value
        return M[r][c];
    else
        // if out of matrix bounds, return an unreachable cell
        return 15;
}

/**
 * Multiply two matrices.
 *
 * @param other Matrix object on right side of the '*' operator.
 *
 * @return A Matrix object representing the product of this matrix and other.
 */
Matrix Matrix::operator*(Matrix other) {
    if(cols != other.rows)
        // ERR: matrices cannot be multiplied (should never happen)
        exit(1);

    Matrix result = Matrix(rows, other.cols);         // init result matrix

    // loop through this.rows
    for(int r=0; r<rows; r++) {
        // loop through other.cols
        for(int c=0; c<other.cols; c++) {
            long double value = 0;                    // default value is 0

            // value = sum of products between corresponding rows and columns
            for(int i=0; i<cols; i++)
                value += get(r, i) * other.get(i, c);

            result.set(r, c, value);
        }
    }

    return result;
}
