#pragma once

#include <vector>

//peak heat flux in W/m^2, time of peak in s, heat load J/m^2
std::vector<double> heating(const std::vector<std::vector<double>>& history, double rnose);
