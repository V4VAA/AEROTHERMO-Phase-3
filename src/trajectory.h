#include <iostream>
#include <cmath>
#include "EquilFlow.h"
#include "aerodynamics.h"
#include "std_atmosphere.h"

using namespace std;

const double R_earth = 6371000.0;
const double g = 9.80665;

//Equations of motion
vector<double> state(double V, double gamma, double h, double rho, double Sref, double CD, double CL, double m, double g)
{
    double Vdot = - rho * V * V * Sref * CD / (2.0 * m) - g * sin(gamma);
    double gammadot = V * cos(gamma) / (R_earth + h) - rho * V * Sref * CL / (2.0 * m) - g * cos(gamma) / U;
    double hdot = V * sin(gamma);

    return {Vdot, gammadot, hdot};
}

void trajectory(double type, double h0, double M0, double m)
{
    double h = h0;
    double gamma = 0.0;
    double M = M0;

    double Sref;    
    if (type == 1){Sref = 1.0;}
    else if (type == 2){Sref = 1.0;}

    while (h > 0.0)
    {
        //Get atmospheric properties
        const vector<double> atmosphere = std_atmosphere(h, M);
        const double rho = atmosphere[3];
        const double a = atmosphere[5];
        double V = M * a;



        //Get aerodynamic coefficients
        const vector<double> coeffs = aerodynamics(type, h, M, AoA);
        const double CN = coeffs[0];
        const double CA = coeffs[1];
        const double CL = coeffs[2];
        const double CD = coeffs[3];
        const double LOD = coeffs[4];


        const double dt = 0.1;

        //RK4 integration

        double k1, k2, k3, k4;
        double l1, l2, l3, l4;
        double m1, m2, m3, m4;

        //step 1
        vector<double> step1 = state(V, gamma, h, rho, Sref, CD, CL, m, g);
        k1, l1, m1 = step1[0], step1[1], step1[2];

        //step 2
        vector<double> step2 = state(V + 0.5 * dt * k1, gamma + 0.5 * dt * l1, h + 0.5 * dt * m1, rho, Sref, CD, CL, m, g);
        k2, l2, m2 = step2[0], step2[1], step2[2];

        //step 3
        vector<double> step3 = state(V + 0.5 * dt * k2, gamma + 0.5 * dt * l2, h + 0.5 * dt * m2, rho, Sref, CD, CL, m, g);
        k3, l3, m3 = step3[0], step3[1], step3[2];

        //step 4
        vector<double> step4 = state(V + dt * k3, gamma + dt * l3, h + dt * m3, rho, Sref, CD, CL, m, g);
        k4, l4, m4 = step4[0], step4[1], step4[2];

        //update state variables

        V = V + dt * (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        gamma = gamma + dt * (l1 + 2*l2 + 2*l3 + l4) / 6.0;
        h = h + dt * (m1 + 2*m2 + 2*m3 + m4) / 6.0;
    }
}