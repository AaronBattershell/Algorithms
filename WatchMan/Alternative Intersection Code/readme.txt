This code defines lines using Ax + By = C as opposed to y = mx + b.

This intersection method fails at different test cases than the y = mx + b method.

One example of code that fails is: 

	line a(point(80, 81), point(139, 140));
	arc b(point(120, 120), point(100, 100), 4, -5);
	cout << a.intersect(b) << endl;

This incorrectly detects an intersection.
