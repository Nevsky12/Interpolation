//
// Created by Asus on 27.09.2022.
//
#include "newton.h"
namespace interpolation
{

scalar newton( vec const &x
             , vec const &y
             , scalar const val
             ) noexcept
{
    scalar result = y[0];

    integer const n = y.size();

    for(integer i = 1u; i < n; ++i)
    {
       scalar f_i = 0.;
       for (integer j = 0u; j <= i; ++j)
       {
           scalar dx = 1.;
           for (integer k = 0u; k <= i; ++k)
               if (k != j)
                   dx *= (x[j] - x[k]);
           f_i += y[j] / dx;
       }
       for (integer j = 0u; j < i; ++j)
           f_i *= (val - x[j]);
       result += f_i;
    }
    return result;
}

}   // namespace interpolation
