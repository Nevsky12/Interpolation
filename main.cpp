#include <iostream>
#include "newton.h"
int main()
{

    std::vector<double> f_x = {0., 0.033, 0.067, 0.100, 0.134, 0.168, 0.203, 0.238, 0.273, 0.309, 0.346};
    std::vector<double>   x = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.};
    double const h  = 0.1;
    double const x0 = 0.95;

    auto const resSpline = interpolation::     naturalSpline(x, f_x, h);
    auto const result    = interpolation::naturalSplineValue(resSpline, x0);
    auto const other     = interpolation::            newton(x, f_x, x0);

    std::cout << "Newton         interpolation result: " << other  << std::endl;
    std::cout << "Natural spline interpolation result: " << result << std::endl; // 0.327426

    return 0;
}
