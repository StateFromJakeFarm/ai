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

double h(vector<double> W, vector<int> X) {
    double WdotX = 0;
    for(unsigned int i=0; i<W.size(); i++)
        WdotX += W[i]*X[i];

    return 1.0 / (1.0 + exp(-1.0*WdotX));
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
            double hj = h(W, X[j]);

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
    double myH = h(W, Q);
    double d0 = pow(pow(myH-0, 2), 0.5);
    double d1 = pow(pow(myH-1, 2), 0.5);
    if(d0 < d1)
        cout << 0 << endl;
    else
        cout << 1 << endl;

    // KNN k=5
    int k = 5;
    vector<double> allDist;
    for(int i=0; i<M-1; i++)
        allDist.push_back(d(Q, X[i]));

    vector<int> nearIndeces;
    double lowestVal = INT_MAX;
    int lowestIndex;
    for(int i=0; i<k; i++) {
        for(int j=0; j<M-1; j++) {
            double curVal = allDist[j];
            if(curVal < lowestVal) {
                lowestVal = curVal;
                lowestIndex = j;
            }
        }

        nearIndeces.push_back(lowestIndex);
        allDist[lowestIndex] = INT_MAX;
        lowestVal = INT_MAX;
    }

    int total0 = 0;
    int total1 = 0;
    for(int i=0; i<k; i++) {
        if(Y[nearIndeces[i]] == 0)
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
