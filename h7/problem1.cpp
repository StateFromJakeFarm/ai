#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    int M, D, N;
    double a;

    cin >> M >> D >> N >> a;

    vector< vector<int> > data;
    data.resize(M);
    for(int r=0; r<M; r++) {
        // add dummy value
        data[r].push_back(1);
        for(int c=0; c<D+1; c++) {
            int val;
            cin >> val;

            data[r].push_back(val);
        }
    }
}
