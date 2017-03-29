#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    int M, D, N;
    long double a;

    cin >> M >> D >> N >> a;

    vector<long double> weights;
    for(int i=0; i<D+1; i++) {
        weights.push_back(1);
    }

    vector<int> answers;

    vector< vector<int> > data;
    data.resize(M);
    for(int r=0; r<M; r++) {
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
        vector<long double> projections;
        for(int x=0; x<M; x++) {
            long double projection = 0;
            for(int i=0; i<D+1; i++) {
                projection += data[x][i]*weights[i];
            }

            projections.push_back(projection);
        }

        // update weights
        for(int i=0; i<D+1; i++) {
            for(int x=0; x<M; x++) {
                weights[i] += a*data[x][i]*(answers[x]-projections[x]);
            }
        }
    }

    // print final weights
    for(int w=0; w<D+1; w++)
        cout << fixed << showpoint << setprecision(12) << weights[w] << endl;

    return 0;
}
