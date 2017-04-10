#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <utility>
#include <string>

using namespace std;

class ANN {
    private:
    long double alpha;
    int k;

    // Hold Neurons' input and activation function output
    struct Neuron {
        long double a;
        long double in;
    };

    // Actual ANN structure composed of neurons and weights
    vector< vector<Neuron> > layers;
    vector< vector<long double> > weights;

    // Digit encodings
    vector< vector<long double> > encodings;

    // Train + test input/output
    vector< vector<long double> > trainIns;
    vector< vector<long double> > testIns;
    vector<long double> trainOuts;
    vector<long double> testOuts;

    // Construct ANN and get input/output
    void constructLayers(char*);
    void getWeights(char*);
    void getDigitEncodings(char*);
    void getIns(char*, vector< vector<long double> >&);
    void getOuts(char*, vector<long double>&);

    // Get input value for neuron
    long double getIn(int, int);
    // Calculate activation function for neuron
    void g(int, int);

    void printWeights();


    public:
    // Constructor
    ANN(char*, char*, char*, char*, char*, char*, char*, long double, int);
    // Run one iteration of back-propagation algo
    void backPropogate();
    // Compare output node values to digit encodings to classify the input
    void classify();
    // Print accuracy of ANN
    void printAccuracy();
};
