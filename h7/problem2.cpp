#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    int M, D, N;
    double a;

    cin >> M >> D >> N >> a;

    // init weights
    vector<double> W;
    for(int j=0; j<D; j++)
        W.push_back(1);

    // build vectors for train data and classifications
    vector< vector<int> > X;
    vector<int> Y;
    vector<int> Q;

    X.resize(M-1);
    for(int j=0; j<M; j++) {
        // dummy weights
        X[j].push_back(1);
        for(int i=0; i<D+1; i++) {
            int cur;
            cin >> cur;

            if (j != M-1) {
                if(i != D)
                    X[j].push_back(cur);
                else
                    Y.push_back(cur);
            } else {
                Q.push_back(cur);
            }
        }
    }

    // main iteration loop
    for(int n=0; n<N; n++) {
        for(int j=0; j<M-1; j++) {
            // get -w <dot> x
            double WdotX = 0;
            for(int i=0; i<D; i++) {
                WdotX += W[i]*X[j][i];
            }

            // get h(Xj)
            double hj = 1.0 / (1.0 + exp(-1.0*WdotX));

            // update all weights
            for(int i=0; i<D; i++) {
                W[i] = W[i] + a*(Y[i]-hj)*hj*(1-hj)*X[j][i];
            }
        }
    }

    for(int i=0; i<D; i++)
        cout << fixed << showpoint << setprecision(12) << W[i] << endl;

    return 0;
}














