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

    struct Neuron {
        long double a;
        long double in;
    };

    vector< vector<Neuron> > layers;
    vector< vector<long double> > weights;

    vector< vector<long double> > encodings;

    vector< vector<long double> > trainIns;
    vector< vector<long double> > testIns;
    vector<long double> trainOuts;
    vector<long double> testOuts;

    void constructLayers(char*);
    void getWeights(char*);
    void getDigitEncodings(char*);
    void getIns(char*, vector< vector<long double> >&);
    void getOuts(char*, vector<long double>&);

    long double getIn(int, int);
    void g(int, int);

    void printWeights();


    public:
    ANN(char*, char*, char*, char*, char*, char*, char*, long double, int);
    void backPropogate();
    void classify();
    void printAccuracy();
};
