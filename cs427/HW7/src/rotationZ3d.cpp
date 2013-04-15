#include "rotationZ3d.h"

//////////////////
// Constructors //
//////////////////
rotationZ3d::rotationZ3d(void) : transformation3d()
{
  // Do Nothing
}


rotationZ3d::rotationZ3d(float angle) : transformation3d()
{
  float s = sin(angle);
  float c = cos(angle);

  _transformation(0,0) = c;
  _transformation(1,0) = s;
  _transformation(0,1) = -s;
  _transformation(1,1) = c;

  _inverseTransformation = _transformation.transpose();
}


rotationZ3d::rotationZ3d(const rotationZ3d& r) : transformation3d(r)
{
  // Do Nothing
}
