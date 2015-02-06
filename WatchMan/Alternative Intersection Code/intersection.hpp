#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cmath>

#define OFFSET 0.000000001
#define TOLLERANCE 0.000001

struct arc;

struct point {
	double x, y;

	point(double x = 0, double y = 0);
	double dist(point p);
};

struct line {
	point one, two;
	double slope, yInt;

	line(point one, point two);
	bool liesOnSegment(point p);
	bool intersect(line l);
	bool intersect(arc c);
	bool parallel(line l);
};

struct arc {
	point one, two, center;
	double dx, dy, radius;

	arc(point one, point two, double dx, double dy);
	bool intersect(line l);
};

#endif
