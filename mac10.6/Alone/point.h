#ifndef _alone_point_
#define _alone_point_

#include <iostream>

class aPoint{
public:
	aPoint();
	aPoint(int _x, int _y);

	bool operator==(const aPoint &) const;
	bool operator<(const aPoint &a) const;

	int x; int y;
};

#endif