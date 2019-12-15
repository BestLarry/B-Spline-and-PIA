#include <iostream>
#include <functional>
#include <imgproc/imgproc.hpp>
#include <highgui/highgui.hpp>
#include "Vec.h"
#include "PIA.h"
#include "BSpline.h"

using namespace cv;
using namespace std;

typedef function<Vec2D(double)> Curve;

Point2d v2p(const Vec2D& v)
{
    return Point2d(v.x, v.y);
}

void DrawCurve(Mat img, Curve curve, const Scalar& color, double begin, double end,
    double interval = 0.01, int thickness = 1, int lineType = LINE_8, int shift = 0)
{
    Point2d old_point = v2p(curve(begin));
    for (double i = begin + interval; i < end - interval; i += interval)
    {
        Point2d new_point = v2p(curve(i + interval));
        line(img, old_point, new_point, color, thickness, lineType, shift);
        old_point = new_point;
    }
}

int main()
{
    Mat img = Mat::zeros(Size(800, 600), CV_8UC3);
    img.setTo(255);              // ÉèÖÃÆÁÄ»Îª°×É«

    vector<Vec2D> controls = { {200,200},{300,300},{400,200} };
    for (auto& v : controls)
    {
        circle(img, v2p(v), 2, Scalar(0, 0, 255), -1);
    }
    vector<double> knots = { 0., 0., 0., 1.0, 1.0, 1.0 };
    size_t degree = 2;
    BSpline c(controls, knots, degree);
    DrawCurve(img, Curve(c), Scalar(0, 0, 0), 0, 1, 0.01);

    auto new_ctrl = CurvePIA(controls, c.base(), { 0.01, 0.5, 0.99 });
    for (auto& v : new_ctrl)
    {
        circle(img, v2p(v), 2, Scalar(255, 0, 255), -1);
    }
    BSpline a(new_ctrl, knots, degree);
    DrawCurve(img, Curve(a), Scalar(0, 255, 0), 0, 1, 0.01);

    imshow("»­°å", img);
    waitKey();

    return 0;
}