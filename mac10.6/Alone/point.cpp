#include "point.h"

aPoint::aPoint(){
	x = 0; y = 0;
}

aPoint::aPoint(int _x, int _y){
	x = _x;
	y = _y;
}

bool aPoint::operator==(const aPoint &p) const{
	return ((p.x == (*this).x && p.y == (*this).y)? true : false);
}

bool aPoint::operator<(const aPoint &a) const{
	if(a.x < (*this).x)
		return true;
	return false;
}