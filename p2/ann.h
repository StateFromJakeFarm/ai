#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

class ANN {
    private:
    long double alpha;
    int k;

    // Neurons to compose the network
    struct Neuron {
        long double a;
        long double delta;
        vector<long double> weights;
    };

    // Actual ANN structure composed of neurons and weights
    vector< vector<Neuron> > layers;

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

    // Print weights of first node to all nodes in next layer
    void printWeights();
    void printNeuron(int, int);


    // Run one iteration of back-propagation algo
    void backPropogate();
    // Compare output node values to digit encodings to classify the input
    void classify();
    // Print accuracy of ANN
    void printAccuracy();

    // Run the ANN's main loop
    void main();

    public:
    // Constructor
    ANN(char*, char*, char*, char*, char*, char*, char*, long double, int);
};
