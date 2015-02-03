This code defines lines using Ax + By = C as opposed to y = mx + b.

This intersection method fails and passes the same test cases as the y = mx + b. There must be an edge case that I am not taking into account but I cannot find it.

One example of code that fails is: 

	line a(point(80, 81), point(21, 140));
	arc b(point(60, 100), point(40, 120), 5, 4);
	cout << a.intersect(b) << endl;

This should detect an intersection but fails to. Originaly I though it was because the points that define the arc form a line that is parallel to the line perpendicular to the dx dy line. I fixed this case by properly assigning the center of the circle but the test cases still fail.

I am at a loss and have no idea how to fix these last few test cases dealing with line-arc intersection.
