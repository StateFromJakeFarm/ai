#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    int M, D, N;
    double a;

    cin >> M >> D >> N >> a;

    vector<double> weights;
    vector<double> answers;

    vector< vector<int> > data;
    data.resize(M);
    for(int r=0; r<M; r++) {
        // start with all weights = 1
        weights.push_back(1);

        // add dummy value
        data[r].push_back(1);
        for(int c=0; c<D+1; c++) {
            int val;
            cin >> val;

            if(c != D)
                data[r].push_back(val);
            else
                answers.push_back(val);
        }
    }

    // main iteration loop
    for(int n=0; n<N; n++) {
        // get projections from current weights h(Xj)
        vector<double> projections;

        // each data vector
        for(int x=0; x<M; x++) {
            double projection = 0;
            // each element of each data vector
            for(int i=0; i<D+1; i++) {
                projection += data[x][i]*weights[i];
            }

            projections.push_back(projection);
        }

        for(int x=0; x<M; x++) {
            for(int i=0; i<D+1; i++) {

            }
        }

        for(int w=0; w<M; w++) {
            
        }
    }

    // print final weights
    for(int w=0; w<M; w++)
        cout << fixed << showpoint << setprecision(12) << weights[w] << endl;

    return 0;
}