#include "rotationY3d.h"

//////////////////
// Constructors //
//////////////////
rotationY3d::rotationY3d(void) : transformation3d()
{
  // Do Nothing
}


rotationY3d::rotationY3d(float angle) : transformation3d()
{
  float s = sin(angle);
  float c = cos(angle);

  _transformation(0,0) = c;
  _transformation(2,0) = -s;
  _transformation(0,2) = s;
  _transformation(2,2) = c;

  _inverseTransformation = _transformation.transpose();
}


rotationY3d::rotationY3d(const rotationY3d& r) : transformation3d(r)
{
  // Do Nothing
}
