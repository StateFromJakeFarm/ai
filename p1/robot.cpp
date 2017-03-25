/**
 * @file robot.cpp Definitions for Robot class methods defined in 'robot.h'.
 *
 * @author Jacob Hansen
 * @date 3/24/16
 **/

#include"robot.h"
#include"matrix.h"

/**
 * Constructor for Robot object.  Initializes a Robot and executes its main
 * iteration loop to print highest probabilities for states at t1 -> tn.
 *
 * @return A Robot object.
 **/
Robot::Robot(Matrix w, long double er, vector<string> o): world(w), e(er), obsvns(o) {
    numStates = world.size;

    main();
}

/**
 * Convert a 'NSWE' string representing the robot's observations at some time
 * to a binary string.
 *
 * @param obs A string representing the robot's observation.
 *
 * @return A bitset<4> object to serve as a binary string analogue.
 **/
bitset<4> Robot::obsToBinary(string obs) {
    bitset<4> bin;
    for(unsigned int i=0; i<obs.length(); i++) {
        char cur = obs[i];
        if(cur == 'N')
            bin[0] = 1;
        else if(cur == 'S')
            bin[1] = 1;
        else if(cur == 'W')
            bin[2] = 1;
        else
            bin[3] = 1;
    }

    return bin;
}

/**
 * Convert a decimal integer value representing the obstacles present
 * at a certain state in the robot's world to a binary string.
 *
 * @param state An integer representing the obstacles in decimal.
 *
 * @return A bitset<4> object to serve as a binary string analogue.
 **/
bitset<4> Robot::decToBinary(int state) {
    bitset<4> bin;
    for(int p=3; p>=0; p--) {
        int pwr = pow(2, p);
        if(state - pwr >= 0) {
            state -= pwr;
            bin[3-p] = 1;
        } else {
            bin[3-p] = 0;
        }
    }

    return bin;
}

/**
 * Create the transitivity matrix for the robot's grid world to hold
 * P(Xt | Xt-1).  Where each column is the 'from' state, and the
 * probabilities in its rows correspond to the 'to' states available.
 *
 * @param world A Matrix object representing the robot's grid world.
 *
 * @param return A Matrix object representing the transitivity matrix.
 */
Matrix Robot::getT(Matrix world) {
    // get total number of cells
    int numCells = world.rows * world.cols;
    // initialize the transitivity matrix as a square of the total number
    // of cells
    Matrix trans(numCells, numCells);

    // loop through all states
    for(int r=0; r<world.rows; r++) {
        for(int c=0; c<world.cols; c++) {
            // get obstacle observation for current state
            int cellVal = world.get(r, c);

            // current state number will be (current row)*(# columns) + 
            // (current column)
            int curState = r*world.cols + c;
            if(cellVal != 15) {
                // if we can visit this state, add its transition probabilities
                // to the transitivity matrix

                // retrieve state numbers for all neighbors
                int neighbs[4];
                neighbs[0] = (r-1)*world.cols + c;
                neighbs[1] = (r+1)*world.cols + c;
                neighbs[2] = r*world.cols + (c-1);
                neighbs[3] = r*world.cols + (c+1);

                // get binary string representation of current cell's value
                bitset<4> cellValBinary = decToBinary(cellVal);
                // record available state numbers
                vector<int> avails;
                for(int i=0; i<4; i++) {
                    if(cellValBinary[i] == 0)
                        avails.push_back( neighbs[i] );
                }

                // assign equal probability to all available nieghbors
                long double prob = 1.0/avails.size();
                for(unsigned int i=0; i<avails.size(); i++) {
                    trans.set(avails[i], curState, prob);
                }
            } else {
                // keep track of unavailable states
                unavails.push_back(curState);
            }
        }
    }

    return trans;
}

/**
 * Calculate the probability of a robot making a certain observation while
 * being in a certain state, P(obs | X).  This function takes into account
 * the robot's sensory error as well using the following equation:
 *      P(obs | X) = e^d * (1-e)^(1-d)
 *
 * @param state A bitset<4> object to hold the sequence of observations
 *        consistent with a state.
 * @param obs A bitset<4> object to hold the robot's sequence of observations.
 *
 * @return A long double representing P(et | Xt).
 **/
long double Robot::P_ObsGivenState(bitset<4> state, bitset<4> obs) {
    long double d = 0;

    // get number of differing bits
    for(int i=0; i<4; i++) {
        if(state[i] != obs[i])
            ++d;
    }

    return pow(e, d) * pow( (1-e), 4-d);
}

/**
 * Construct observation matrix to hold the probabilities of making an
 * observation given that the robot is currently in a certain state,
 * P(obs | X).
 **/
Matrix Robot::getO(bitset<4> obs) {
    // observation matrix is a sqaure of the number of states
    Matrix obsMatrix(numStates, numStates);

    // loop through each state (possible and not)
    for(int r=0; r<world.rows; r++) {
        for(int c=0; c<world.cols; c++) {
            int curState = r*world.cols + c;
            // get the binary string representing the ideal observation for
            // this state
            bitset<4> worldState = decToBinary(world.get(r, c));

            // calculate and add probabilities to the matrix
            obsMatrix.set(curState, curState, P_ObsGivenState(worldState, obs));
        }
    }

    return obsMatrix;
}

/**
 * For each observation, print calculate and print to screen the highest
 * probability for the robot's location, as well as all states tied for
 * that probability.
 */
void Robot::main() {
    // get the transitivity matrix
    Matrix T = getT(world);

    // initialize the joint prediction matrix for time t=0
    Matrix J(numStates, 1); 
    // all available states begin with equal probability
    long double startingProb = 1.0 / (numStates - unavails.size());

    // add starting probability to all available states
    int unavailsItr = 0;
    for(int r=0; r<numStates; r++) {
        if(unavails[unavailsItr] == r)
            ++unavailsItr;
        else
            J.set(r, 0, startingProb);
    }

    // get probabilities for time t=1, P(Xt | Yt-1)
    J = T * J;

    for(unsigned int i=0; i<obsvns.size(); i++) {
        // set observation matrix
        Matrix O = getO(obsToBinary(obsvns[i]));

        // set matrix Y to hold probabilities for robot being in each state
        // given the validity of our observation at the current time,
        // P(obs | Xt) * P(Xt | Yt-1).
        Matrix Y = O * J;

        J = T * Y;

        // get the sum of cells in Y and highest probability in this iteration
        long double sum = 0;

        long double highestProb = 0;
        long double cur;
        for(int r=0; r<Y.rows; r++) {
            cur = Y.get(r, 0);
            if(cur > highestProb)
                highestProb = cur;

            sum += cur;
        }

        // print highest probability and all states having this probability
        cout << showpoint << fixed << setprecision(12) << highestProb / sum << " ";
        for(int r=0; r<Y.rows; r++) {
            if(Y.get(r, 0) == highestProb)
                cout << r << " ";
        }
        cout << endl;
    }
}
