/**
 * @file matrix.h Declaration of matrix class.
 *
 * @author Jacob Hansen
 * @date 3/24/2016
 */

#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<fstream>

using namespace std;

class Matrix {
    public:
    //~Member Variables~//
    // dimensions
    int rows, cols;
    // number of cells
    int size;
    // 2-D vector as implementing data structure
    vector< vector<long double> >M;

    //~Constructors~//
    // create 0x0
    Matrix();
    // create RxC matrix with cell values defaulted to 0
    Matrix(int, int);
    // create a matrix read from a string wherein each line of characters
    // represents one row of the rectangular matrix
    Matrix(string);

    //~Methods~//
    // set value of a cell
    void set(int, int, long double);
    // get value of a cell
    long double get(int, int);

    // overload '*' operator to multiply matrices
    Matrix operator*(Matrix);
};

#endif // MATRIX_H
