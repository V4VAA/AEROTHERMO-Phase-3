#pragma once

#include <vector>

//AoA is in radians. M <= 1 uses the no-shock approximation.
std::vector<double> aerodynamics(int type, double P, double T, double rho, double V, double M, double AoA);
