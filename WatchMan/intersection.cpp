#include "intersection.hpp"
#include <utility>
using namespace std;

point::point(double x, double y)
    : x(x), y(y)
{ }

double point::dist(point p) {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
}

line::line(point one, point two)
    : one(one), two(two), slope((one.y - two.y) / (one.x - two.x)), yInt(one.y - slope * one.x)
{ }

bool line::liesOnSegment(point p) {
	return one.dist(p) + two.dist(p) - one.dist(two) < 0.00001;
}

// Returns true if two line segments intersect
bool line::intersect(line l) {
    double xInt = (yInt - l.yInt) / (l.slope - slope);
    point lineInt(xInt, l.slope * xInt + l.yInt);

	return l.liesOnSegment(lineInt) && liesOnSegment(lineInt);
}

bool line::intersect(arc c) {
    return c.intersect(*this);
}

arc::arc(point one, point two, double dx, double dy) 
	: one(one), two(two), dx(dx), dy(dy) { 
	
	point centerOfGivenPoints((one.x + two.x) / 2, (one.y + two.y) / 2);
	line lineToCenter1(point(one.x, one.y), point(one.x - dy, one.y + dx));
	line lineToCenter2(point(centerOfGivenPoints.x, centerOfGivenPoints.y), 
		point(centerOfGivenPoints.x + (one.x - two.x), centerOfGivenPoints.y - (one.y - two.y)));

	double xInt = (lineToCenter1.yInt - lineToCenter2.yInt) / (lineToCenter2.slope - lineToCenter1.slope);
	center.x = xInt;
	center.y = lineToCenter2.slope * xInt + lineToCenter2.yInt;

	radius = center.dist(one);
	startAngle = atan2(one.y - center.y, one.x - center.x);
	endAngle = atan2(two.y - center.y, two.x - center.x);

	if ((one.x - center.x) * dx - (one.y - center.y) * dy < 0) {
		swap(startAngle, endAngle);
	}
}

// Returns true if a line segment and arc intersect
bool arc::intersect(line l) {
	double A = pow(l.slope, 2) + 1;
	double B = 2 * (l.slope * l.yInt - l.slope * center.y - center.x);
	double C = pow(center.y, 2) - pow(radius, 2) + pow(center.x, 2) - 2 * l.yInt * center.y + pow(l.yInt, 2);
	double D = pow(B, 2) - 4 * A * C;

	/* Note: D > 0 : Zero intersection points
	 *       D == 0: One intersection point
	 *       D < 0 : Two intersection points
	*/
	if (D < 0) {
		return false;
	}
	if (D >= 0) {
		double xInt = (-B + sqrt(D)) / 2 * A;
		double yInt = l.slope * xInt + l.yInt;
		double IntAngle = acos(xInt / radius);

		//cout << xInt << ' ' << yInt << endl;
		if (IntAngle >= startAngle && IntAngle <= endAngle && l.liesOnSegment(point(xInt, yInt))) {
			return true;
		}
	}
	if (D > 0) {
		double xInt = (-B - sqrt(D)) / 2 * A;
		double yInt = l.slope * xInt + l.yInt;
		double IntAngle = acos(xInt / radius);

		//cout << xInt << ' ' << yInt << endl;
		if (IntAngle >= startAngle && IntAngle <= endAngle && l.liesOnSegment(point(xInt, yInt))) {
			return true;
		}
	}

	return false;
}
