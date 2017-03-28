#include <iostream>
#include <climits>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

double d(vector<int> q, vector<int> x) {
    double res = 0;
    for(unsigned int i=0; i<q.size(); i++) {
        res += pow(q[i]-x[i], 2);
    }

    return pow(res, 0.5);
}

int main() {
    int M, D, N;
    double a;

    cin >> M >> D >> N >> a;

    // init weights
    vector<double> W;
    for(int j=0; j<D+1; j++)
        W.push_back(1);

    // build vectors for train data and classifications
    vector< vector<int> > X;
    vector<int> Y;
    vector<int> Q;

    X.resize(M-1);
    for(int j=0; j<M; j++) {
        // dummy weights
        if(j != M-1)
            X[j].push_back(1);
        else
            Q.push_back(1);
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
            for(int i=0; i<D+1; i++) {
                WdotX += W[i]*X[j][i];
            }

            // get h(Xj)
            double hj = 1.0 / (1.0 + exp(-1.0*WdotX));

            // update all weights
            for(int i=0; i<D+1; i++) {
                W[i] += a*(Y[j]-hj)*hj*(1-hj)*X[j][i];
            }
        }
    }

    // print weights
    for(int i=0; i<D+1; i++)
        cout << fixed << showpoint << setprecision(12) << W[i] << endl;

    // h(Q)
    double h = 0;
    for(int i=0; i<D+1; i++) {
        h += W[i]*Q[i];
    }
    if(h < 0.5)
        cout << 0 << endl;
    else
        cout << 1 << endl;

    // KNN k=5
    int k=5;
    int nears[5];
    int nearsIndeces[5];
    for(int i=0; i<k; i++)
        nears[i] = INT_MAX;

    for(int i=0; i<M-1; i++) {
        double dist = d(Q, X[i]);

        // keep track of k nearest neighbors
        for(int j=0; j<k; j++) {
            if(nears[j] > dist) {
                double cur = nears[j];
                nears[j] = dist;
                nearsIndeces[j] = i;

                // shift everything after insert
                for(int q=j+1; q<D+1; q++) {
                    double next = nears[q];
                    nears[q] = cur;
                    cur = next;
                }
            }
        }
    }

    int total0 = 0;
    int total1 = 0;
    for(int i=0; i<k; i++) {
        if(Y[nearsIndeces[i]] == 0)
            ++total0;
        else
            ++total1;
    }
    if(total0 > total1)
        cout << 0 << endl;
    else
        cout << 1 << endl;

    return 0;
}
