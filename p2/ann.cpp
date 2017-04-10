#include "ann.h"

//PARSE INPUT FILES//
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
        inputs.resize(curLine+1);

        istringstream ss(line);

        for(int i=0; i<numInputNeurons; i++) {
            ss >> curVal;
            inputs[curLine].push_back(curVal);
        }

        ++curLine;
    }

    f.close();
}

void ANN::getOuts(char* fname, vector<long double> &outputs) {
    ifstream f(fname);

    long double curVal;
    while(f >> curVal)
        outputs.push_back(curVal);

    f.close();
}

// print weights of 1st node to all nodes it's attached to
void ANN::printWeights() {

}

//NEURON FUNCTIONS//
/*
long double ANN::getIn(int l, int n) {
    return 1;
}

void ANN::g(int l, int n) {
    
}
*/

//MAIN PUBLIC INTERFACE//
ANN::ANN(char* train_input, char* train_out, char* test_input, char* test_out, char* structure, char* weights, char* encoding, long double a, int numIters) {
    constructLayers(structure);
    getWeights(weights);
    getDigitEncodings(encoding);
    getOuts(train_out, trainOuts);
    getOuts(test_out, testOuts);
    getIns(train_input, trainIns);
    getIns(test_input, testIns);

    alpha = a;
    k = numIters;

    main();
}

void ANN::backPropogate() {

}

void ANN::classify() {

}

void ANN::printAccuracy() {

}

void ANN::main() {
    // Iterations
    for(int i=0; i<k; i++) {
        // Each input vector
        for(unsigned int xi=0; xi<trainIns.size(); xi++) {
            int curNeuron = 0;

            // Set input ai's to input vector values
            for(int n=0; n<layers[0].size(); n++) {
                layers[0][n].a = trainIns[xi][n];
                cout << "input layer: " << curNeuron << endl;
                ++curNeuron;
            }

            // Steps 2 and 3
            for(unsigned int l=1; l<layers.size(); l++) {
                for(unsigned int n=0; n<layers[l].size(); n++) {
                    // Get "in" value for this neuron
                    long double in = 0;
                    for(int prev=0; prev<layers[l-1].size(); prev++)
                        in += weights[l-1][prev];

                    // Get activation function for this neuron
                    layers[l][curNeuron].a = 1 / (1 + exp(in));
                    cout << curNeuron << " " << layers[l][curNeuron].a << endl;

                    ++curNeuron;
                }
            }
        }
    }
}










