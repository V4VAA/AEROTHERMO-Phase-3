#pragma once

#include <vector>

//AoA is in radians.
std::vector<double> aerodynamics(int type, double P, double T, double rho, double V, double AoA);
