#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cmath>

#define PI 3.14159

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
};
	
struct arc {
	point one, two, center;
	double dx, dy, radius, startAngle, endAngle;
	
	arc(point one, point two, double dx, double dy);
	bool intersect(line l);
};

#endif
