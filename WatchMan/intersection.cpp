#include "intersection.hpp"
#include <utility>
#include <iostream>
using namespace std;

point::point(double x, double y)
    : x(x), y(y)
{ }

double point::dist(point p) {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
}

line::line(point one, point two)
	: one(one.x + OFFSET, one.y + OFFSET), two(two.x - OFFSET, two.y - OFFSET), slope((this->one.y - this->two.y) / (this->one.x - this->two.x)), yInt(this->one.y - slope * this->one.x)
{ }

bool line::liesOnSegment(point p) {
	return one.dist(p) + two.dist(p) - one.dist(two) < 0.00001;
}

bool line::parallel(line l) {
	return (one.x - two.x == l.one.x - l.two.x && one.y - two.y == l.one.y - l.two.y);
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
	
	if (lineToCenter1.parallel(lineToCenter2)) {
			double xInt = (lineToCenter1.yInt - lineToCenter2.yInt) / (lineToCenter2.slope - lineToCenter1.slope);
			center.x = xInt;
			center.y = lineToCenter2.slope * xInt + lineToCenter2.yInt;
	}
	else {
			center = centerOfGivenPoints;
	}

	radius = center.dist(one);
}

// Returns true if a line segment and arc intersect
bool arc::intersect(line l) {
	cout << l.slope << endl;
	double A = pow(l.slope, 2) + 1;
	double B = 2 * (l.slope * l.yInt - l.slope * center.y - center.x);
	double C = pow(center.y, 2) - pow(radius, 2) + pow(center.x, 2) - 2 * l.yInt * center.y + pow(l.yInt, 2);
	double D = pow(B, 2) - 4 * A * C;

	/* Note: D < 0 : Zero intersection points
	 *       D == 0: One intersection point
	 *       D > 0 : Two intersection points
	*/
	if (D < 0) {
		//cout << "No int: " << D << endl;
		return false;
	}
	
	line arcPointsLine(point(one.x, one.y), point(two.x, two.y));

	if (true || D >= 0) {
		double xInt = (-B + sqrt(D)) / 2 * A;
		double yInt = l.slope * xInt + l.yInt;

		line dxdyIntLine(point(xInt, yInt), point(one.x + dx, one.y + dy));

		double crossXInt = (arcPointsLine.yInt - dxdyIntLine.yInt) / (dxdyIntLine.slope - arcPointsLine.slope);
		point lineInt(crossXInt, dxdyIntLine.slope * crossXInt + dxdyIntLine.yInt);

		cout << "Intersection: " << xInt << ' ' << yInt << endl;

		if (!dxdyIntLine.liesOnSegment(lineInt) && l.liesOnSegment(point(xInt, yInt))) {
			return true;
		}
	}
	if (true || D > 0) {
		double xInt = (-B - sqrt(D)) / 2 * A;
		double yInt = l.slope * xInt + l.yInt;

		line dxdyIntLine(point(xInt, yInt), point(one.x + dx, one.y + dy));

		double crossXInt = (arcPointsLine.yInt - dxdyIntLine.yInt) / (dxdyIntLine.slope - arcPointsLine.slope);
		point lineInt(crossXInt, dxdyIntLine.slope * crossXInt + dxdyIntLine.yInt);

		cout << "Intersection: " << xInt << ' ' << yInt << endl;

		if (!dxdyIntLine.liesOnSegment(lineInt) && l.liesOnSegment(point(xInt, yInt))) {
			return true;
		}
	}

	return false;
}

