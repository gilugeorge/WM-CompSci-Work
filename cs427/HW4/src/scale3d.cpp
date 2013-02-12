#include "scale3d.h"

//////////////////
// Constructors //
//////////////////
scale3d::scale3d(void) : transformation3d()
{
  // Do Nothing
}


scale3d::scale3d(float uniformScale) : transformation3d()
{
  // HW4: implement this
  //      returns: nothing
  //      modifies: sets the member variables (defined in transformation3d), such that it represents a uniform scale
	_transformation = mat3d(uniformScale);
	_inverseTransformation = mat3d(1/uniformScale);
}


scale3d::scale3d(float scaleX, float scaleY, float scaleZ) : transformation3d()
{
  // HW4: implement this
  //      returns: nothing
  //      modifies: sets the member variables (defined in transformation3d), such that it represents a non-uniform cale
	_transformation(0,0) = scaleX;
	_transformation(1,1) = scaleY;
	_transformation(2,2) = scaleZ;
	
	_inverseTransformation(0,0) = 1/scaleX;
	_inverseTransformation(1,1) = 1/scaleY;
	_inverseTransformation(2,2) = 1/scaleZ;
	
}

scale3d::scale3d(const scale3d& s) : transformation3d(s)
{
  // Do Nothing
}
