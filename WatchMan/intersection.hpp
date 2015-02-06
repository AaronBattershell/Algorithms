#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cmath>

#define ndef -3000000
#define TOLLERANCE 0.000001

struct arc;

struct point {
	double x, y;

	point(double x = 0, double y = 0);
	point(const point &p);
	double dist(point p);
};

struct line {
	point one, two;
	double A, B, C;

	line(point one, point two);
	point getIntersect(line l);	
	bool parallel(line l);
	bool perpendicular(line l);
	bool liesOnSegment(point p);
	bool intersect(line l);
	bool intersect(arc c);
};

struct arc {
	point one, two, center;
	double dx, dy, radius;

	arc(point one, point two, double dx, double dy);
	bool intersect(line l);
};

#endif
