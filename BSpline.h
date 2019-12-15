#ifndef __BSPLINE__
#define __BSPLINE__

#include <vector>
#include "Vec.h"
#include <iostream>

class BSpline
{
private:
	std::vector<Vec2D> P;
	std::vector<double> K;
	int degree;
	std::vector<std::vector<Base>> funcs;  //funcs[degree][n]

public:
	BSpline(const std::vector<Vec2D>& controls, const std::vector<double>& knots, size_t degree)
		: P(controls), K(knots), degree(degree)
	{
		// 0½×
		funcs.push_back({});
		for (size_t i = 0; i < knots.size() - 1; i++)
		{
			double l = knots[i];
			double r = knots[i + 1];
			auto b = [l, r](double t) { return l <= t && t < r ? 1.0 : 0.0; };
			funcs.back().push_back(b);
		}
		for (size_t d = 1; d <= degree; d++)
		{
			funcs.push_back({});
			for (size_t i = 0; i < knots.size() - 1 - d; i++)
			{
				double k_i = knots[i];
				double k_i_1 = knots[i + 1];
				double k_i_d = knots[i + d];
				double k_i_d_1 = knots[i + 1 + d];
				auto b = [k_i, k_i_1, k_i_d, k_i_d_1, d, i, this](double t)
				{
					double d1 = k_i_d - k_i, d2 = k_i_d_1 - k_i_1, f1 = 0, f2 = 0;
					if (d1 == 0.0)
						f1 = 1.0;
					else
						f1 = (t - k_i) / d1;
					if (d2 == 0.0)
						f2 = 1.0;
					else
						f2 = (k_i_d_1 - t) / d2;
						return f1 * funcs[d - 1][i](t) + f2 * funcs[d - 1][i + 1](t);
				};
				funcs.back().push_back(b);
			}
		}
	}
	Vec2D operator()(double t)
	{
		Vec2D ret = { 0,0 };
		for (int i = 0; i < P.size(); i++)
		{
			ret += P[i] * funcs.back()[i](t);
		}
		return ret;
	}
	auto base()
	{
		return funcs.back();
	}
	auto knots()
	{
		return K;
	}
};

#endif // !__BSPLINE__
