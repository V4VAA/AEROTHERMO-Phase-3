#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "trajectory.h"
#include "heating.h"

using namespace std;

int main()
{
    
    const vector<vector<double>> cases =
    {
        // type, h0 (m), V0 (m/s), gamma0 (rad), AoA (rad), m (kg), Sref (m^2), rnose (m)

        // Examples
        {1, 75.0, 1250.0, -0.25, 0.0, 1000.0, 1.0, 0.1},
        {2, 75.0, 1250.0, -0.25, 0.0, 1000.0, 1.0, 0.1}
    };

    ofstream results("results.csv");
    ofstream histories("trajectory.csv");
    if (!results || !histories)
    {
        cerr << "Could not open output files\n";
        return 1;
    }

    results << setprecision(12) << "case,type,peak_heat_flux_W_m2,peak_time_s,heat_load_J_m2\n";
    histories << setprecision(12) << "case,time_s,V_m_s,gamma_rad,h_m\n";

    int case_number = 0;
    for (const auto& inputs : cases)
    {
        ++case_number;
        const int type = static_cast<int>(inputs[0]);
        const double h0 = inputs[1];
        const double V0 = inputs[2];
        const double gamma0 = inputs[3];
        const double AoA = inputs[4];
        const double m = inputs[5];
        const double Sref = inputs[6];
        const double rnose = inputs[7];

        const vector<vector<double>> history = trajectory(type, h0, V0, gamma0, AoA, m, Sref);
        for (const auto& state : history)
        {
            histories << case_number << ',' << state[0] << ',' << state[1] << ',' << state[2] << ',' << state[3] << '\n';
        }

        cout << "\nCase " <<  case_number << "trajectory sim done \n"<< endl;

        const vector<double> aeroheating = heating(history, rnose);
        results << case_number << ',' << type << ',' << aeroheating[0] << ',' << aeroheating[1] << ',' << aeroheating[2] << '\n';

        cout << "Case " <<  case_number << "heating sim done \n"<< endl;
    }

    return 0;
}
