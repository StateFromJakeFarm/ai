#include"matrix.h"
#include"robot.h"

using namespace std;

int main(int argc, char* argv[]) {
    // file name holding grid world
    string fName;
    // robot's sensory error
    long double e;
    // vector to hold all robot's 'NSWE' observations
    vector<string> obsvns;

    if (argc > 1) {
        string cur;
        for(int i=1; i<argc; i++) {
            if(i == 1) {
                fName = argv[i];
            } else if(i == 2) {
                istringstream ss(argv[i]);
                ss >> e;
            } else {
                cur = argv[i];
                obsvns.push_back(cur);
            }
        }
    } else {
        cin >> fName >> e;

        string obs;
        while(cin >> obs)
            obsvns.push_back(obs);
    }

    // create the robot's grid world
    Matrix world(fName);

    // initialize the robot and run its main iteration loop
    Robot WallE(world, e, obsvns);

    return 0;
}
