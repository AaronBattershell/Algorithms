#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cmath>

// Forward delcaration required to satisify line definition
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
	bool intersect(line l);
	bool intersect(arc c);
};
	
struct arc {
	point one, two, tan;
	
	arc(point one, point two, point tan);
	bool intersect(line l);
};

#endif
