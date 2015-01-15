#include <cmath>
using namespace std;

struct point {
	point(double x = 0, double y = 0) 
		: x(x), y(y) { }
	
	double x, y;

	double dist(point p) {
		return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
	}
};
	
struct line {
	line(point one, point two)
		: one(one), two(two), slope((one.y - two.y) / (one.x - two.x)), yInt(one.y - slope * one.x) { }

	point one, two;
	double slope;
	double yInt;

	// Returns true if two line segments intersect
	bool intersect(line l) {
		double xInt = (yInt - l.yInt) / (l.slope - slope);
		point lineInt(xInt, l.slope * xInt + l.yInt);
	
		// Determin if the eventual intersection of extended line segements A and B lies on 
		// both of those line segments 
		return l.one.dist(lineInt) + l.two.dist(lineInt) - l.one.dist(l.two) < 0.00001
			&& one.dist(lineInt) + two.dist(lineInt) - one.dist(two) < 0.00001;
	}
};
	
struct arc {
	arc(point one, point two, point tan) 
		: one(one), two(two), tan(tan) { }
	
	point one, two, tan;
	
	// Returns true if a line segment and arc intersect
	bool intersect(line l) {
		// TODO: Implement line and arc intersection detection

		return false;
	}
};

