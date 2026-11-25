#pragma once

#include <vector>

//Angles are in radians. History columns are t (s), V (m/s), gamma (rad), h (m).
std::vector<std::vector<double>> trajectory(int type, double h0, double V0, double gamma0, double AoA, double m, double Sref);
