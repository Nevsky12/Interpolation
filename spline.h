//
// Created by Asus on 27.09.2022.
//
#pragma once
#include <vector>
namespace interpolation
{

using scalar  =             double ;
using vec     = std::vector<double>;

using integer = unsigned int;

struct SplineCoefficients
{
    scalar a;
    scalar b;
    scalar c;
    scalar d;
    scalar x;
};

std::vector<SplineCoefficients> naturalSpline( vec    const &x
                                             , vec    const &y
                                             , scalar const h
                                             ) noexcept;

scalar                     naturalSplineValue( std::vector<SplineCoefficients> const &data
                                             , scalar                          const x
                                             ) noexcept;

}   // namespace spline
