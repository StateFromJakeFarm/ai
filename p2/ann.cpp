#include "ann.h"

//PARSE INPUT FILES//
void ANN::constructLayers(char* fname) {
    layers.resize(1);

    ifstream f(fname);

    int numNodes;
    int numLayers = 1;
    while(f >> numNodes) {
        ++numLayers;
        layers.resize(numLayers);
        layers[numLayers-1].resize(numNodes);
    }

    f.close();
}

void ANN::getWeights(char* fname) {
    ifstream f(fname);

    int numNeurons = 0;
    long double curWeight;
    // loop through all layers except output layer
    for(unsigned int l=1; l<layers.size()-1; l++) {
        for(unsigned int n=0; n<layers[l].size(); n++) {
            // for each node in next layer, add weight to vector for
            // current node
            for(unsigned int i=0; i<layers[l+1].size(); i++) {
                f >> curWeight;
                layers[l][n].weights.push_back(curWeight);
            }

            ++numNeurons;
        }
    }

    f.close();

    // Add dummy weights
    layers[0].resize(1);
    for(int i=0; i<numNeurons+layers[layers.size()-1].size(); i++)
        layers[0][0].weights.push_back(0.01);
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

    int numInputNeurons = layers[1].size();

    int curLine = 0;
    string line;
    long double curVal;
    while(getline(f, line)) {
        ++curLine;
        inputs.resize(curLine);

        istringstream ss(line);

        for(int i=0; i<numInputNeurons; i++) {
            ss >> curVal;
            inputs[curLine-1].push_back(curVal);
        }
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
/*
    int curNeuron = layers[0].size();
    for(unsigned int n=0; n<layers[1].size(); n++) {
        cout << showpoint << fixed << setprecision(12) << weights[0][curNeuron] << " ";
        ++curNeuron;
    }
    cout << endl;
*/
    int curNeuron = 0;
    for(unsigned int l=0; l<layers.size(); l++) {
        for(unsigned int n=0; n<layers[l].size(); n++) {
            cout << curNeuron << ": ";
            for(unsigned int w=0; w<layers[l][n].weights.size(); w++)
                cout << layers[l][n].weights[w] << " ";
            cout << endl;
            ++curNeuron;
        }
    }
}


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
            // Set input ai's to input vector values (1)
            for(int n=0; n<layers[1].size(); n++) {
                layers[1][n].a = trainIns[xi][n];
            }

            // Get "in" values and activation functions (2 and 3)
            for(unsigned int l=2; l<layers.size(); l++) {
                for(unsigned int n=0; n<layers[l].size(); n++) {
                    // Get "in" value for this neuron
                    long double in = layers[0][0].weights[n];
                    for(unsigned int p=0; p<layers[l-1].size(); p++)
                        in += layers[l-1][p].weights[n] * layers[l-1][p].a;

                    // Get activation function for this neuron
                    layers[l][n].a = 1 / (1 + exp(-1 * in));
                }
            }

            // Get errors for output layer (4)
            int outputL = layers.size()-1;
            for(unsigned int n=0; n<layers[outputL].size(); n++) {
                long double an = layers[outputL][n].a;
                layers[outputL][n].delta = an * (1 - an) * (trainOuts[n] - an);
            }

            // Get errors for layers (output, 1] (5 and 6)
            for(int l=outputL-1; l>0; l--) {
                for(unsigned int n=0; n<layers[l].size(); n++) {
                    long double an = layers[l][n].a;

                    // Get sum of products of errors and weights leaving this
                    // neuron
                    long double productSum = 0;
                    for(unsigned int j=0; j<layers[l+1].size(); j++) {
                        productSum += layers[l+1][j].delta * layers[l][n].weights[j];
                    }

                    layers[l][n].delta = an * (1 - an) * productSum;
                }
            }

            // Update weights (7)
            for(unsigned int l=1; l<layers.size()-1; l++) {
                for(unsigned int n=0; n<layers[l].size(); n++) {
                    long double an = layers[l][n].a;
                    for(unsigned int j=0; j<layers[l+1].size(); j++) {
                        layers[l][n].weights[j] += alpha * layers[l][n].a * layers[l+1][j].delta;
cout << layers[l][n].weights[j] << endl;
                    }
                }
            }
        }
    }
}










