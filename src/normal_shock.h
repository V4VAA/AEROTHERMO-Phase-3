#pragma once

constexpr double gamma_cpg = 1.4;
constexpr double Rair = 287.0;
constexpr double eqlibMach = 5.0;

struct NormalShockState
{
    double P;
    double T;
    double rho;
    double V;
};

NormalShockState cpgNormalShock(double P, double T, double rho, double V, double M);
