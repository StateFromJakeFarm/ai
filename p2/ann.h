#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class ANN {
    private:
    long double alpha;
    int k;

    class Neuron {
        public:
        long double ai;
        long double in;
    };

    vector< vector<Neuron> > layers;
    vector< vector<long double> > weights;

    vector< vector<long double> > encodings;

    vector< vector<long double> > trainIns;
    vector< vector<long double> > testIns;
    vector<long double> trainOuts;
    vector<long double> testOuts;

    void constructLayers(string);
    void getWeights(string);
    void getDigitEncodings(string);
    void getIns(string, vector< vector<long double> >&);
    void getOuts(string, vector<long double>&);


    public:
    ANN(string, string, string, string, string, string, string, long double, int);
};
