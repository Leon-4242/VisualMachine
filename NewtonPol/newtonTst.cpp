#include <iostream>
#include "newton.h"
using namespace std;

int main() {
    vector<double> x;
    vector<double> y;
    vector<double> a;

    size_t n;
    cout << "Number of nodes: ";
    cin >> n;
    x.resize(n);
    y.resize(n);
    cout << "Input nodes x:" << endl;
    for (size_t i = 0; i < n; ++i) {
        cin >> x[i];
    }
    cout << "Input nodes y:" << endl;
    for (size_t i = 0; i < n; ++i) {
        cin >> y[i];
    }
    computeNewtonPol(x, y, a);
    while (true) {
        double t;
        cout << "t: ";
        cin >> t;
        if (!cin)
            break;
        cout << "p(t) = " << newtonPolValue(x, a, n-1, t) << endl;
    }

    return 0;
}
