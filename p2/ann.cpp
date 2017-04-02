#include "ann.h"

ANN::ANN(string train_input, string train_out, string test_input, string structure, string weights, string encoding, long double a, int numIters) {
    constructLayers(structure);
    getWeights(weights);
    getDigitEncodings(encoding);
    getOuts(train_out);
    getIns(train_input, trainIns);
    getIns(test_input, testIns);
}

void ANN::constructLayers(string fname) {
    ifstream f(fname.c_str());

    int numNodes;
    int curSize;
    while(f >> numNodes) {
        int curSize = layers.size();
        layers.resize(curSize+1);
        layers[curSize-1].resize(numNodes);
    }

    f.close();
}

void ANN::getWeights(string fname) {
    ifstream f(fname.c_str());

    long double curWeight;
    for(unsigned int l=0; l<layers.size(); l++) {
        for(unsigned int i=0; i<layers[l].size(); i++) {
            for(unsigned int n=0; n<layers[i+1].size(); i++) {
                f >> curWeight;
                weights[i][n] = curWeight;
            }
        }
    }

    f.close();
}
