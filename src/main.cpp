#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <exception>
#include <vector>

#include "std_atmosphere.h"
#include "trajectory.h"
#include "heating.h"
#include "EquilFlow.h"
#include "stag_properties.h"

using namespace std;

const double pi = 3.14159265358979323846;

int main() {
    //set up initial conditions


    //iterate thruogh the different initial conditions

    for ()
    {
        //evaluate the trajectory
        vector<vector<double>> history = trajectory(type, h0, V0, gamma0, AoA, m, Sref);

        //evaluate the heating
        vector<double> aeroheating = heating(history);

        //write the results to a file
        ofstream outfile("results.csv");
        
    }



    return 0;
}
