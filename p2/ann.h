#include <iostream>
#include <fstream>
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
        vector< pair<int, long double> > inWeights;
    };

    vector< vector<Neuron> > layers;
    vector< vector<long double> > trainIns;
    vector<long double> trainOuts;
    vector< vector<long double> > testIns;

    public:
    void constructLayers(string fname);
    void getWeights(string fname);
    void getDigitEncodings(string fname);
    void getIns(string fname);
    void getOuts(string fname);
};
