#include "heating.h"

#include <cmath>
#include "EquilFlow.h"
#include "normal_shock.h"
#include "std_atmosphere.h"

using namespace std;

static double stagnationPressure(const NormalShockState& postShock, double gamma)
{
    const double M2_squared = postShock.rho * postShock.V * postShock.V / (gamma * postShock.P);
    return postShock.P * pow(1.0 + 0.5 * (gamma - 1.0) * M2_squared, gamma / (gamma - 1.0));
}

vector<double> heating(const vector<vector<double>>& history, double rnose)
{
    const double T_w = 300.0; //cold wall assumption
    const double mu_w = 1.458e-6 * pow(T_w, 1.5) / (T_w + 110.4);
    const double k_sg = 1.74153e-4;

    double peak = 0.0;
    double peak_time = 0.0;
    double heat_load = 0.0;
    double prev_q = 0.0;
    double prev_t = 0.0;
    bool first = true;

    for (const auto& state : history)
    {
        const double t = state[0];
        const double V = state[1];
        const double h = state[3];

        const vector<double> atmosphere = std_atmosphere(h < 0.0 ? 0.0 : h, 0.0);
        const double rho_inf = atmosphere[3];
        const double M = V / atmosphere[5];

        double q = 0.0;
        if (M >= eqlibMach)
        {
            const double P_inf = atmosphere[0];
            const double T_inf = atmosphere[1];
            EquilFlow air("E10");
            air.NormalShock(P_inf, T_inf, V);
            const NormalShockState postShock = {air.mix.P, air.mix.T, air.mix.rho, air.mix.U2};

            const double P_e = stagnationPressure(postShock, air.mix.gamma);
            const double h_e = 1000.0 * air.mix.h + 0.5 * postShock.V * postShock.V;
            air.Composition(2, P_e, h_e / 1000.0);
            const double rho_e = air.mix.rho;
            const double mu_e = air.mix.mu;
            const double Pr_e = air.mix.Pr;

            air.Composition(1, T_w, P_e);
            const double rho_w = air.mix.rho;
            const double h_w = 1000.0 * air.mix.h;

            //Stagnation point Fay-Riddell heating
            const double grad_u_e = sqrt(2.0 * (P_e - P_inf) / rho_e) / rnose;
            q = 0.763 * pow(Pr_e, -0.6) * pow(rho_w * mu_w, 0.1) * pow(rho_e * mu_e, 0.4) * sqrt(grad_u_e) * (h_e - h_w);
        }
        else if (M >= 1.2)
        {
            q = k_sg * sqrt(rho_inf / rnose) * pow(V, 3);
        }

        if (first || q > peak)
        {
            peak = q;
            peak_time = t;
        }
        if (!first) {heat_load += 0.5 * (prev_q + q) * (t - prev_t);}
        prev_q = q;
        prev_t = t;
        first = false;
    }

    return {peak, peak_time, heat_load};
}
