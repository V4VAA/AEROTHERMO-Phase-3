#include <iostream>
#include <cmath>
#include "EquilFlow.h"
#include "aerodynamics.h"
#include "std_atmosphere.h"

using namespace std;

const double R_earth = 6371000.0;
const double g_0 = 9.80665;

//Equations of motion
vector<double> state(double V, double gamma, double h, double rho, double Sref, double CD, double CL, double m, double g)
{
    double Vdot = - rho * V * V * Sref * CD / (2.0 * m) - g * sin(gamma);
    double gammadot = V * cos(gamma) / (R_earth + h) - rho * V * Sref * CL / (2.0 * m) - g * cos(gamma) / V;
    double hdot = V * sin(gamma);

    return {Vdot, gammadot, hdot};
}

vector<double> getcoefficients(int type, double altitude, double V, double AoA)
{
            //Get atmospheric properties
        const vector<double> atmosphere = std_atmosphere(altitude, 0.0);
        const double rho = atmosphere[3];
        const double a = atmosphere[5];
        const double M = V / a;


        //Get aerodynamic coefficients
        const vector<double> coeffs = aerodynamics(type, altitude, M, AoA);
        const double CL = coeffs[2];
        const double CD = coeffs[3];

        double g = g_0 * pow(R_earth / (R_earth + altitude), 2.0);

        return {CD, CL, rho, g};
}

void trajectory(int type, double h0, double V0, double gamma0, double AoA, double m)
{
    double h = h0;
    double gamma = gamma0;
    double V = V0;

    const double dt = 0.1;

    double Sref;    
    if (type == 1){Sref = 1.0;}
    else if (type == 2){Sref = 1.0;}

    while (h > 0.0)
    {
        //RK4 integration
        double k1, k2, k3, k4;
        double l1, l2, l3, l4;
        double m1, m2, m3, m4;

        double CD, CL, rho, g;

        //step 1 -----------------------------------
        vector<double> coefficients = getcoefficients(type, h, V, AoA);
        CD = coefficients[0];
        CL = coefficients[1];
        rho = coefficients[2];
        g = coefficients[3];

        vector<double> step1 = state(V, gamma, h, rho, Sref, CD, CL, m, g);
        k1 = step1[0];
        l1 = step1[1];
        m1 = step1[2];

        //step 2 -----------------------------------
        V = V + 0.5 * dt * k1;
        gamma = gamma + 0.5 * dt * l1;
        h = h + 0.5 * dt * m1;

        coefficients = getcoefficients(type, h, V, AoA);
        CD = coefficients[0];
        CL = coefficients[1];
        rho = coefficients[2];
        g = coefficients[3];

        vector<double> step2 = state(V, gamma, h, rho, Sref, CD, CL, m, g);
        k2 = step2[0];
        l2 = step2[1];
        m2 = step2[2];

        //step 3 -----------------------------------
        V = V + 0.5 * dt * k2;
        gamma = gamma + 0.5 * dt * l2;
        h = h + 0.5 * dt * m2;

        coefficients = getcoefficients(type, h, V, AoA);
        CD = coefficients[0];
        CL = coefficients[1];
        rho = coefficients[2];
        g = coefficients[3];

        vector<double> step3 = state(V, gamma, h, rho, Sref, CD, CL, m, g);
        k3 = step3[0];
        l3 = step3[1];
        m3 = step3[2];

        //step 4 -----------------------------------
        V = V + dt * k3;
        gamma = gamma + dt * l3;
        h = h + dt * m3;

        coefficients = getcoefficients(type, h, V, AoA);
        CD = coefficients[0];
        CL = coefficients[1];
        rho = coefficients[2];
        g = coefficients[3];

        vector<double> step4 = state(V, gamma, h, rho, Sref, CD, CL, m, g);
        k4 = step4[0];
        l4 = step4[1];
        m4 = step4[2];

        //update state variables

        V = V + dt * (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        gamma = gamma + dt * (l1 + 2*l2 + 2*l3 + l4) / 6.0;
        h = h + dt * (m1 + 2*m2 + 2*m3 + m4) / 6.0;
    }
}