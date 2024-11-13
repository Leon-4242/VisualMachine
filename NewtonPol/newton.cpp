#include <cmath>
#include <cassert>
#include "newton.h"

using namespace std;

// Newton polynomial for nodes x0, x1, ..., xn
//        with coefficients    a0, a1, ..., an
// p(x) = a0 + a1(x-x0) + a2(x-x0)(x-x1) + ... +
//        a_n(x-x0)(x-x1)...(x-x_n-1)

double newtonPolValue(
    const std::vector<double>& x,
    const std::vector<double>& a,
    size_t n,
    double t
) {
    assert(n <= x.size() - 1);
    assert(n <= a.size() - 1);

    // p(x) = a0 + a1(x-x0) + a2(x-x0)(x-x1) + ... +
    //        a_n(x-x0)(x-x1)...(x-x_n-1)
    double s = a[0];
    double p = 1.;
    for (size_t i = 1; i <= n; ++i) {
        p *= (t - x[i-1]);
        s += a[i]*p;
    }
    return s;
}

void computeNewtonPol(
    const std::vector<double>& x,
    const std::vector<double>& y,
    std::vector<double>& a
) {
    if (x.size() == 0) {
        a.clear();
        return;
    }
    size_t n = x.size() - 1;
    a.resize(n + 1);
    // a_n+1 = (y_n+1 - p_n(x_n+1)) /
    //         (x_n+1 - x0)(x_n+1 - x1)...(x_n+1 - x_n)
    a[0] = y[0];
    for (size_t i = 1; i <= n; ++i) {
        double p = 1.;
        for (size_t j = 0; j < i; ++j) {
            p *= (x[i] - x[j]);
        }
        a[i] = (y[i] - newtonPolValue(x, a, i-1, x[i]))/p;
    }
}
