#include "intersection.hpp"
#include <utility>
#include <iostream>
using namespace std;

point::point(double x, double y)
	: x(x), y(y)
{ }

point::point(const point &p)
	: x(p.x), y(p.y)
{ }

double point::dist(point p) {
	return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
}

line::line(point one, point two)
	: one(one.x, one.y), two(two.x, two.y), A(this->one.y - this->two.y), B(this->two.x - this->one.x), C(this->one.x * this->two.y - this->two.x * this->one.y)
{ }

point line::getIntersect(line l) {
	// Check for special cases like vertical and or horizontal lines
	if (parallel(l)) {
		return point(ndef, ndef);
	}
	else if (!A && !l.B) { // this horizontal, l vertical
		return point(-l.C / l.A, -C / B);
	}
	else if (!B && !l.A) { // this vertical, l horizontal
		return l.getIntersect(*this);
	}
	else if (!A) { // this horizontal
		return point((-l.B * -C / B - l.C) / l.A, -C / B);
	}
	else if (!l.A) { // l horizontal
		return l.getIntersect(*this);
	}
	else if (!B) { // this vertical
		return point(-C / A, (-l.A * -C / A - l.C) / l.B);
	}
	else if (!l.B) { // l vertical
		return l.getIntersect(*this);
	}
	else { // neither this nor l vertical or horizontal
		// Solve for Ax1 + By1 - C1 = Ax2 + By2 - C2 
		double yInt = (C * -l.C - A * l.C) / (-B * l.A + A * l.B);
		double xInt = (-B * yInt - C) / A;

		return point(xInt, yInt);
	}
}

bool line::parallel(line l) {
	return (abs((one.y - two.y) / (one.x - two.x) - (l.one.y - l.two.y) / (l.one.x - l.two.x)) < TOLLERANCE) ||
		(abs(one.x - two.x) < TOLLERANCE && abs(l.one.x - l.two.x) < TOLLERANCE) ||
		((abs(one.y - two.y) < TOLLERANCE && abs(l.one.y - l.two.y) < TOLLERANCE));
}

bool line::perpendicular(line l) {
	return (abs((one.y - two.y) / (one.x - two.x) + (l.one.y - l.two.y) / (l.one.x - l.two.x)) < TOLLERANCE) ||
		(abs(one.x - two.x) < TOLLERANCE && abs(l.one.y - l.two.y) < TOLLERANCE) ||
		((abs(one.y - two.y) < TOLLERANCE && abs(l.one.x - l.two.x) < TOLLERANCE));
}

bool line::liesOnSegment(point p) {
	return one.dist(p) + two.dist(p) - one.dist(two) < TOLLERANCE;
}

// Returns true if two line segments intersect
bool line::intersect(line l) {
	point lineInt(getIntersect(l));

	return lineInt.x != ndef && l.liesOnSegment(lineInt) && liesOnSegment(lineInt);
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

	if (!lineToCenter2.perpendicular(line(one, two))) {
		center = lineToCenter1.getIntersect(lineToCenter2);
	}
	else {
		center = centerOfGivenPoints;
	}

	radius = center.dist(one);
}


// Returns true if a line segment and arc intersect
bool arc::intersect(line l) {
	// Center the line and arc
	line centerLine(point(l.one.x - center.x, l.one.y - center.y), point(l.two.x - center.x, l.two.y - center.y));
	arc centerArc(point(one.x - center.x, one.y - center.y), point(two.x - center.x, two.y - center.y), dx, dy);

	double DX = centerLine.two.x - centerLine.one.x;
	double DY = centerLine.two.y - centerLine.one.y;
	double DR = sqrt(pow(DX, 2) + pow(DY, 2));
	double D = centerLine.one.x * centerLine.two.y - centerLine.two.x * centerLine.one.y;

	double intersections = pow(centerArc.radius, 2) * pow(DR, 2) - pow(D, 2);

	// Note: intersections < 0 : Zero intersection points
	//       intersections == 0: One intersection point
	//       intersections > 0 : Two intersection points
	if (intersections < 0) {
		return false;
	}

	line arcPointsLine(centerArc.one, centerArc.two);

	if (intersections >= 0) {
		double xInt = (D * DY + (DY < 0 ? -1 : 1) * DX * sqrt(pow(centerArc.radius, 2) * pow(DR, 2) - pow(D, 2))) / pow(DR, 2);
		double yInt = (-centerLine.A * xInt - centerLine.C) / centerLine.B;

		point intersectionPoint(xInt, yInt);

		line dxdyIntLine(intersectionPoint, point(centerArc.one.x + dx, centerArc.one.y + dy));
		point crossingPoint = arcPointsLine.getIntersect(dxdyIntLine);

		if (arcPointsLine.parallel(dxdyIntLine) || (crossingPoint.x != ndef && !dxdyIntLine.liesOnSegment(crossingPoint) && centerLine.liesOnSegment(intersectionPoint))) {
			return true;
		}
	}
	if (intersections > 0) {
		double xInt = (D * DY - (DY < 0 ? -1 : 1) * DX * sqrt(pow(centerArc.radius, 2) * pow(DR, 2) - pow(D, 2))) / pow(DR, 2);
		double yInt = (-centerLine.A * xInt - centerLine.C) / centerLine.B;

		point intersectionPoint(xInt, yInt);

		line dxdyIntLine(intersectionPoint, point(centerArc.one.x + dx, centerArc.one.y + dy));
		point crossingPoint = arcPointsLine.getIntersect(dxdyIntLine);

		if (arcPointsLine.parallel(dxdyIntLine) || (crossingPoint.x != ndef && !dxdyIntLine.liesOnSegment(crossingPoint) && centerLine.liesOnSegment(intersectionPoint))) {
			return true;
		}
	}

	return false;
}

