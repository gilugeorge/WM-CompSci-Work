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
  _transformation.setDiagonal(uniformScale);
  _inverseTransformation.setDiagonal(1.0f / uniformScale);
}


scale3d::scale3d(float scaleX, float scaleY, float scaleZ) : transformation3d()
{
  _transformation.setDiagonal( vec3d(scaleX, scaleY, scaleZ) );
  _inverseTransformation.setDiagonal( vec3d(1.0f / scaleX, 1.0f / scaleY, 1.0f / scaleZ) );
}

scale3d::scale3d(const scale3d& s) : transformation3d(s)
{
  // Do Nothing
}
