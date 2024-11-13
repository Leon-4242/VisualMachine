#ifndef NEWTON_H
#define NEWTON_H

#include <vector>

// Newton polynomial for nodes x0, x1, ..., xn
//        with coefficients    a0, a1, ..., an
// p(x) = a0 + a1(x-x0) + a2(x-x0)(x-x1) + ...
//           + a_n(x-x0)(x-x1)...(x-x_n-1)

// Compute the value of Newton polynomial
double newtonPolValue(
    const std::vector<double>& x, // Nodes of interpolation
    const std::vector<double>& a, // Coefficcients of Newton polynomial
    size_t n,           // Degree of Newton polynomial == number of nodes - 1
    double t            // Point in which we calculate the value
);                      //       of Newton polynomial
  
// Compute the coefficients of Newton polynomial
void computeNewtonPol(      
    const std::vector<double>& x,   // Nodes of interpolation
    const std::vector<double>& y,   // Values of the polynomial in nodes
    std::vector<double>& a          // Out: coefficients of polynomial
);

#endif
