#include "Utilities.h"

#include <iostream>
#include <sstream>

void barycentricCoords(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p,
                       float &l1, float &l2, float &l3) {
//   float detT = (p1.x - p3.x)*(p2.y - p3.y) - ((p1.y - p3.y)*(p2.x - p3.x));
//   l1 = ((p2.y - p3.y)*(p.x - p3.x) + (p3.x - p2.x)*(p.y - p3.y))/detT;
//   l2 = ((p3.y - p1.y)*(p.x - p3.x) + (p1.x - p3.x)*(p.y - p3.y))/detT;
//   l3 = 1.0 - l1 - l2;
   float area = cross(p2 - p1, p3 - p1).length();
   l1 = cross(p1 - p, p2 - p).length()/area;
   l2 = cross(p2 - p, p3 - p).length()/area;
//   l3 = cross(p2 - p1, p - p1).length()/area;
   l3 = 1.0 - l1 - l2;
}


float strToFloat(const char *str)
{
	float val;
	std::string string(str);
 	std::stringstream stream;
	stream << string;
	stream >> val;

	return val;
}
