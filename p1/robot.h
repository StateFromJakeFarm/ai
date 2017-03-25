/**
 * @file robot.h Declaration of robot class to handle matrix math
 *  behind global robot localization.
 *
 * @author Jacob Hansen
 * @date 3/24/2016
 */

#ifndef ROBOT_H
#define ROBOT_H

#include"matrix.h"
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<iomanip>
#include<bitset>

using namespace std;

class Robot {
    public:
    //~Constructor~//
    Robot(Matrix, long double, vector<string>);

    private:
    //~Member Variables~//
    // holds the NSWE obstacle values for each cell in the robot's world in
    // decimal
    Matrix world;
    // error in robot's sensory observations
    long double e;
    // hold robot's observations at each iteration
    vector<string> obsvns;

    // total number of states in world
    int numStates;
    // hold state numbers for uninhabitable states in robot's world
    vector<int> unavails;

    //~Methods~//
    // convert robot's sensory observation to binary string
    bitset<4> obsToBinary(string);
    // convert world's NSWE obstacle values from decimal to binary string
    bitset<4> decToBinary(int);

    // get values for observaion matrix
    long double P_ObsGivenState(bitset<4>, bitset<4>);

    // create transitivity matrix
    Matrix getT(Matrix);
    // create observation matrix
    Matrix getO(bitset<4>);

    // run the robot's main iteration loop
    void main();
};

#endif // ROBOT_H
