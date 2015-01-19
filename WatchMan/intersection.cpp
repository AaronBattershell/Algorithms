#include "intersection.hpp"
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

// Returns true if two line segments intersect
bool line::intersect(line l) {
    double xInt = (yInt - l.yInt) / (l.slope - slope);
    point lineInt(xInt, l.slope * xInt + l.yInt);

    // Determine if the eventual intersection of extended line segments A and B lies on
    // both of those line segments
    return l.one.dist(lineInt) + l.two.dist(lineInt) - l.one.dist(l.two) < 0.00001
        && one.dist(lineInt) + two.dist(lineInt) - one.dist(two) < 0.00001;
}

bool line::intersect(arc c) {
    return c.intersect(*this);
}

arc::arc(point one, point two, point tan) 
	: one(one), two(two), tan(tan) 
{ }

// Returns true if a line segment and arc intersect
bool arc::intersect(line l) {
	// TODO: Implement line and arc intersection detection

	return false;
}
