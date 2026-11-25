#include <iostream>
#include <cmath>
#include <stdexcept>

#include "aerodynamics.h"
#include "EquilFlow.h"

using namespace std;

const double pi = 3.14159265358979323846;

vector<double> aerodynamics(int type, double P, double T, double rho, double V, double AoA)
{
    EquilFlow aero("E10");
    aero.NormalShock(P, T, V);
    if (!isfinite(aero.mix.rho) || aero.mix.rho <= 0.0)
    {
        throw runtime_error("invalid post-shock density");
    }
    const double epsilon = rho / aero.mix.rho; //Rho_inf/Rho_2

    if (type == 1)
    {
        aero.AeroEllipsoid(epsilon, AoA);
    }
    else
    {
        const double delta_c = 30.0;
        const double L = 1.75;
        const double c = 1.2;

        aero.BiParaAero(L, c, epsilon, delta_c, AoA * 180.0 / pi);
    }

    return {aero.CN, aero.CA, aero.CL, aero.CD, aero.LOD};
}
