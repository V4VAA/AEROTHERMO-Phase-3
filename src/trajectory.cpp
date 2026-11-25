#include "trajectory.h"

#include <cmath>
#include <stdexcept>
#include "aerodynamics.h"
#include "std_atmosphere.h"

using namespace std;

constexpr double R_earth = 6371000.0;
constexpr double g_0 = 9.80665;

//Equations of motion
static vector<double> state(int type, double V, double gamma, double h, double AoA, double Sref, double m)
{
    if (h <= 0.0) {return {};}

    //Get atmospheric properties
    const vector<double> atmosphere = std_atmosphere(h, 0.0);
    const double P = atmosphere[0];
    const double T = atmosphere[1];
    const double rho = atmosphere[3];
    const double a = atmosphere[5];

    //Stop at the limit of the normal-shock model
    if (V <= a) {return {};}

    //Get aerodynamic coefficients
    const vector<double> coeffs = aerodynamics(type, P, T, rho, V, AoA);
    const double CL = coeffs[2];
    const double CD = coeffs[3];
    const double g = g_0 * pow(R_earth / (R_earth + h), 2.0);

    double Vdot = - rho * V * V * Sref * CD / (2.0 * m) - g * sin(gamma);
    double gammadot = V * cos(gamma) / (R_earth + h) + rho * V * Sref * CL / (2.0 * m) - g * cos(gamma) / V;
    double hdot = V * sin(gamma);

    return {Vdot, gammadot, hdot};
}

vector<vector<double>> trajectory(int type, double h0, double V0, double gamma0, double AoA, double m, double Sref)
{
    double h = h0;
    double gamma = gamma0;
    double V = V0;
    double t = 0.0;

    const double dt = 0.1;
    vector<vector<double>> history = {{t, V, gamma, h}};

    while (h > 0.0)
    {
        //RK4 integration
        double k1, k2, k3, k4;
        double l1, l2, l3, l4;
        double m1, m2, m3, m4;

        //step 1 -----------------------------------
        vector<double> step1 = state(type, V, gamma, h, AoA, Sref, m);
        if (step1.empty()) {break;}
        k1 = step1[0];
        l1 = step1[1];
        m1 = step1[2];

        //step 2 -----------------------------------
        vector<double> step2 = state(type, V + 0.5 * dt * k1, gamma + 0.5 * dt * l1, h + 0.5 * dt * m1, AoA, Sref, m);
        if (step2.empty()) {break;}
        k2 = step2[0];
        l2 = step2[1];
        m2 = step2[2];

        //step 3 -----------------------------------
        vector<double> step3 = state(type, V + 0.5 * dt * k2, gamma + 0.5 * dt * l2, h + 0.5 * dt * m2, AoA, Sref, m);
        if (step3.empty()) {break;}
        k3 = step3[0];
        l3 = step3[1];
        m3 = step3[2];

        //step 4 -----------------------------------
        vector<double> step4 = state(type, V + dt * k3, gamma + dt * l3, h + dt * m3, AoA, Sref, m);
        if (step4.empty()) {break;}
        k4 = step4[0];
        l4 = step4[1];
        m4 = step4[2];

        //update state variables

        V = V + dt * (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        gamma = gamma + dt * (l1 + 2*l2 + 2*l3 + l4) / 6.0;
        h = h + dt * (m1 + 2*m2 + 2*m3 + m4) / 6.0;
        t = t + dt;
        if (h <= 0.0) {break;}
        history.push_back({t, V, gamma, h});
    }

    return history;
}
