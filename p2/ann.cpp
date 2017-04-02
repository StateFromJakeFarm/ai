#include "ann.h"

ANN::ANN(string train_input, string train_out, string test_input, string test_out, string structure, string weights, string encoding, long double a, int numIters) {
    constructLayers(structure);
    getWeights(weights);
    getDigitEncodings(encoding);
    getOuts(train_out, trainOuts);
    getOuts(test_out, testOuts);
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

void ANN::getDigitEncodings(string fname) {
    ifstream f(fname.c_str());

    long double curVal;
    for(int d=0; d<10; d++) {
        for(int i=0; i<10; i++) {
            f >> curVal;
            encodings[d][i] = curVal;
        }
    }

    f.close();
}

void ANN::getIns(string fname, vector< vector<long double> > &inputs) {
    ifstream f(fname.c_str());

    int numInputNeurons = layers[0].size();

    int curLine = 0;
    string line;
    long double inVal;
    while(getline(f, line)) {
        inputs.resize(inputs.size()+1);

        istringstream ss(line);

        for(int i=0; i<numInputNeurons; i++) {
            ss >> curVal;
            inputs[curLine].push_back(curVal);
        }
    }

    f.close();
}

void ANN::getOuts(string fname, vector<long double> &outputs) {
    ifstream f(fname.c_str());

    long double curVal;
    for(unsigned int i=0; i<outputs.size(); i++) {
        f >> curVal;
        outputs.push_back(curVal);
    }

    f.close();
}




















