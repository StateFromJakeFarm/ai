#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    int M, D, N;
    double a;

    cin >> M >> D >> N >> a;

    vector< vector<int> > X;
    vector<int> Y;
    for(int j=0; j<M; j++) {
        // dummy weights
        X[j].push_back(1);
        for(int i=0; i<D+1; i++) {
            int cur;
            cin >> cur;

            if(i != D)
                X[j].push_back(cur);
            else
                Y.push_back(cur);
        }
    }

    return 0;
}
