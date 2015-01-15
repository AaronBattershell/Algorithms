#include <cmath>
using namespace std;

namespace {
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
	};

	struct arc {
		arc(point one, point two, point tan) 
			: one(one), two(two), tan(tan) { }
		
		point one, two, tan;
	};

	// Returns true if two line segments intersect
	bool intersect(line a, line b) {
		double xInt = (b.yInt - a.yInt) / (a.slope - b.slope);
		point lineInt(xInt, a.slope * xInt + a.yInt);

		// Determin if the eventual intersection of extended line segements A and B lies on 
		// both of those line segments. 
		return a.one.dist(lineInt) + a.two.dist(lineInt) - a.one.dist(a.two) < 0.00001
			&& b.one.dist(lineInt) + b.two.dist(lineInt) - b.one.dist(b.two) < 0.00001;
	}

	// Returns true if a line segment and arc intersect
	bool intersect(line a, arc b) {
		// TODO: Implement line and arc intersection detection

		return false;
	}
}

// Overload for use with two lines
bool intersect(double line1x1, double line1y1, double line1x2, double line1y2, 
		double line2x1, double line2y1, double line2x2, double line2y2) {

	return intersect(line(point(line1x1, line1y1), point(line1x2, line1y2)), line(point(line2x1, line2y1), point(line2x2, line2y2)));
}

// Overload for use with a line and arc
bool intersect(double line1x1, double line1y1, double line1x2, double line1y2, 
		double arc1x1, double arc1y1, double arc1x2, double arc1y2, double arc1x3, double arc1y3) {

	return intersect(line(point(line1x1, line1y1), point(line1x2, line1y2)), arc(point(arc1x1, arc1y1), point(arc1x2, arc1y2), point(arc1x3, arc1y3)));
}
