//
// Created by Asus on 27.09.2022.
//
#include "spline.h"

namespace interpolation
{

std::vector<SplineCoefficients> naturalSpline(vec const &x, vec const &y, scalar const h) noexcept
{
    vec a;
    vec b;
    vec c;
    vec d;
    vec m;
    vec l;
    vec z;
    vec alpha;

    a.insert(a.begin(), y.begin(), y.end());

    integer const n = a.size() - 1u;

    b.resize(n);
    d.resize(n);
    c.resize(n + 1);
    l.resize(n + 1);
    m.resize(n + 1);
    z.resize(n + 1);

    l[0] = 1.;
    z[0] = 0.;
    m[0] = 0.;
    alpha.push_back(0.);

    for (integer i = 1u; i < n; ++i)
        alpha.push_back((3. * (a[i + 1] - a[i]) - 3. * (a[i] - a[i - 1])) / h);

    for (integer i = 1u; i < n; ++i)
    {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h * m[i - 1];
        m[i] = h / l[i];
        z[i] = (alpha[i] - h * z[i - 1]) / l[i];
    }

    l[n] = 1.;
    z[n] = 0.;
    c[n] = 0.;

    for (integer i = n - 1; i > 0; --i)
    {
        c[i] = z[i] - m[i] * c[i + 1];
        b[i] = (a[i + 1] - a[i]) / h - h * (c[i + 1] + 2 * c[i]) / 3.;
        d[i] = (c[i + 1] - c[i]) / (3. * h);
    }

    std::vector<SplineCoefficients> result(n);
    for (integer i = 0u; i < n; ++i)
    {
        result[i].a = a[i];
        result[i].b = b[i];
        result[i].c = c[i];
        result[i].d = d[i];
        result[i].x = x[i];
    }

    return result;
}

scalar naturalSplineValue(std::vector<SplineCoefficients> const &data, scalar const x) noexcept
{
    integer const n = data.size();
    vec intervals;

    for (auto const item: data)
        intervals.push_back(item.x);

    if (x >= intervals.back())
    {
        auto const &[a, b, c, d, x0] = data.back();
        return a + b * (x - x0) + c * (x - x0) * (x - x0) + d * (x - x0) * (x - x0) * (x - x0);
    }

    for (integer i = 0u; i < n - 1; ++i)
    {
        if (intervals[i] <= x <= intervals[i + 1])
        {
            auto const &[a, b, c, d, x0] = data[i];
            return a + b * (x - x0) + c * (x - x0) * (x - x0) + d * (x - x0) * (x - x0) * (x - x0);
        }
    }
}

}   // namespace spline
