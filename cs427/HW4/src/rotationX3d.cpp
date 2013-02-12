#include "rotationX3d.h"

//////////////////
// Constructors //
//////////////////
rotationX3d::rotationX3d(void) : transformation3d()
{
  // Do Nothing
}


rotationX3d::rotationX3d(float angle) : transformation3d()
{
  float s = sin(angle);
  float c = cos(angle);

  _transformation(1,1) = c;
  _transformation(2,1) = s;
  _transformation(1,2) = -s;
  _transformation(2,2) = c;

  _inverseTransformation = _transformation.transpose();
}


rotationX3d::rotationX3d(const rotationX3d& r) : transformation3d(r)
{
  // Do Nothing
}
