#include "normal_shock.h"

NormalShockState cpgNormalShock(double P, double T, double rho, double V, double M)
{
    const double P_ratio = (2.0 * gamma_cpg * M * M - (gamma_cpg - 1.0)) / (gamma_cpg + 1.0);
    const double rho_ratio = (gamma_cpg + 1.0) * M * M / ((gamma_cpg - 1.0) * M * M + 2.0);

    return {P * P_ratio, T * P_ratio / rho_ratio, rho * rho_ratio, V / rho_ratio};
}
