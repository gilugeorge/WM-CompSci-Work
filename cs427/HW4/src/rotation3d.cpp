#include "rotation3d.h"

//////////////////
// Constructors //
//////////////////
rotation3d::rotation3d(void) : transformation3d()
{
  // Do Nothing
}


rotation3d::rotation3d(float angle, const vec3d& axis) : transformation3d()
{
  // HW4: implement this.
  //      returns: nothing
  //      modifies: sets the member variables (defined in transformation3d) such that it performs a rotation of specified 'angle' along an 'axis'
	
	float c = cos(angle);
	float s = sin(angle);
	_transformation(0,0) = c+(axis[0]*axis[0]*(1-c));
	_transformation(0,1) = (axis[0]*axis[1]*(1-c))-(axis[2]*s);
	_transformation(0,2) = (axis[1]*s)+(axis[0]*axis[2]*(1-c));
	_transformation(1,0) = (axis[2]*s)+(axis[0]*axis[1]*(1-c));
	_transformation(1,1) = c+(axis[1]*axis[1]*(1-c));
	_transformation(1,2) = (-axis[0]*s)+(axis[1]*axis[2]*(1-c));
	_transformation(2,0) = (-axis[1]*s)+(axis[0]*axis[2]*(1-c));
	_transformation(2,1) = (axis[0]*s)+(axis[1]*axis[2]*(1-c));
	_transformation(2,2) = c+(axis[2]*axis[2]*(1-c));

  _inverseTransformation = _transformation.transpose();	
}


rotation3d::rotation3d(const rotation3d& r) : transformation3d(r)
{
  // Do Nothing
}
