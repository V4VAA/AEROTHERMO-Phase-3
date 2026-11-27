#include <cmath>
#include <stdexcept>

#include "aerodynamics.h"
#include "normal_shock.h"
#include "EquilFlow.h"

using namespace std;

const double pi = 3.14159265358979323846;

vector<double> aerodynamics(int type, double P, double T, double rho, double V, double M, double AoA)
{
    EquilFlow aero("E10");
    double rho_2 = rho; //No shock at M <= 1
    if (M >= eqlibMach)
    {
        aero.NormalShock(P, T, V);
        rho_2 = aero.mix.rho;
    }
    else if (M > 1.0)
    {
        rho_2 = cpgNormalShock(P, T, rho, V, M).rho;
    }
    if (!isfinite(rho_2) || rho_2 <= 0.0)
    {
        throw runtime_error("invalid post-shock density");
    }
    const double epsilon = rho / rho_2; //Rho_inf/Rho_2

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
