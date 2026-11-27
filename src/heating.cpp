#include <iostream>
#include <cmath>

#include "EquilFlow.h"
#include "std_atmosphere.h"

using namespace std;

const double Rair = 287;

vector<double> cpgNormalShock(double V, double P, double T, double rho)
{
    double P_ratio = 0;
    double rho_ratio = 0;
    double T_ratio = 0;
    
    double P2 = P * P_ratio;
    double rho2 = rho * rho_ratio;
    double T2 = T * T_ratio;

    double Cp = Rair * T2;


    return {P2, T2, rho2, Cp};
}




vector<double> heating(vector<vector<double>> history)
{
    
    const double T_w = 300.0; //cold wall assumption

    for (const auto& state : history)
    {

        // Stagnation point heating ------------------------------------------
        const double V = state[1];
        const double h = state[3];

        //Get atmospheric properties
        const vector<double> atmosphere = std_atmosphere(h, 0.0);
        const double P_inf = atmosphere[0];
        const double T_inf = atmosphere[1];
        const double rho_inf = atmosphere[3];
        const double a = atmosphere[5];

        double P_2, T_2, rho_2, Cp;
        
        if (V >= 5 * a)
        {
            EquilFlow aero("E10");
            aero.NormalShock(P_inf, T_inf, V);

            P_2 = aero.mix.P;
            T_2 = aero.mix.T;
            rho_2 = aero.mix.rho;
            Cp = aero.mix.Cp;
        }
        else if (a <= V < 5 * a)
        {
            vector<double> normal = cpgNormalShock(V, P_inf, T_inf, rho_inf);
            P_2 = normal[0];
            T_2 = normal[1];
            rho_2 = normal[2];
            Cp = normal[3];
        }
        else
        {
            P_2 = P_inf;
            T_2 = T_inf;
            rho_2 = rho_inf;
            Cp = 3.5 * Rair * T_inf;
        }


        const double rho_w = rho_2 * T_2 / T_w;
        


        // Heating at the offset point ------------------------------------------

        

    }



    return {0.0};
}