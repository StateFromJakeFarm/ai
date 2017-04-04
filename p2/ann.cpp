#include "ann.h"

ANN::ANN(char* train_input, char* train_out, char* test_input, char* test_out, char* structure, char* weights, char* encoding, long double a, int numIters) {
    constructLayers(structure);
    getWeights(weights);
    getDigitEncodings(encoding);
//    getOuts(train_out, trainOuts);
//    getOuts(test_out, testOuts);
//    getIns(train_input, trainIns);
//    getIns(test_input, testIns);

    alpha = a;
    k = numIters;
}

void ANN::constructLayers(char* fname) {
    ifstream f(fname);

    int numNodes;
    int numLayers = 0;
    while(f >> numNodes) {
        ++numLayers;
        layers.resize(numLayers);
        layers[numLayers-1].resize(numNodes);
    }

    f.close();
}

void ANN::getWeights(char* fname) {
    ifstream f(fname);

    int curNeuron = 0;
    long double curWeight;
    // loop through all layers except output layer
    for(unsigned int l=0; l<layers.size()-1; l++) {
        for(unsigned int i=0; i<layers[l].size(); i++) {
            // add new vector of weights for each new node
            weights.resize(curNeuron+1);
            // for each node in next layer, add weight to vector for
            // current node
            for(unsigned int n=0; n<layers[l+1].size(); n++) {
                f >> curWeight;
                weights[curNeuron].push_back(curWeight);
            }

            ++curNeuron;
        }
    }

    f.close();
}

void ANN::getDigitEncodings(char* fname) {
    ifstream f(fname);

    encodings.resize(10);

    long double curVal;
    for(int d=0; d<10; d++) {
        for(int i=0; i<10; i++) {
            f >> curVal;
            encodings[d].push_back(curVal);
        }
    }

    f.close();
}

void ANN::getIns(char* fname, vector< vector<long double> > &inputs) {
    ifstream f(fname);

    int numInputNeurons = layers[0].size();

    int curLine = 0;
    string line;
    long double curVal;
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

void ANN::getOuts(char* fname, vector<long double> &outputs) {
    ifstream f(fname);

    long double curVal;
    for(unsigned int i=0; i<outputs.size(); i++) {
        f >> curVal;
        outputs.push_back(curVal);
    }

    f.close();
}

long double ANN::getIn(int l, int n) {
    return 1;
}

void ANN::g(int l, int n) {
    
}


















