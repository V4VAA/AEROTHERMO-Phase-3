#include <iostream>
#include <cmath>

#include "EquilFlow.h"

using namespace std;

const double pi = 3.14159265358979323846;

vector<double> aerodynamics(double type, double altitude, double Mach, double AoA)
{
    EquilFlow aero("E10");
    vector<double> properties = aero.NormalShock(altitude, Mach);
    double epsilon = properties[30] / properties[21]; //Rho_inf/Rho_2

    if (type == 1)
    {
        aero.AeroEllipsoid(epsilon, AoA);
        return {aero.CN, aero.CA, aero.CL, aero.CD, aero.LOD};
    }
    else if (type == 2)
    {
        const double delta_c = 30.0 * pi / 180.0;
        const double L = 1.75;
        const double c = 1.2;

        aero.BiParaAero(L, c, epsilon, delta_c, AoA);
        return {aero.CN, aero.CA, aero.CL, aero.CD, aero.LOD};
    }
    
}