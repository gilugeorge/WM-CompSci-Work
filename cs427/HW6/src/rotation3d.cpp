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
  vec3d norm_axis = axis.normalize();
  float s = sin(angle);
  float c = cos(angle);

  _transformation(0,0) = c + ((norm_axis.x * norm_axis.x) * (1.0f - c));
  _transformation(0,1) = -(norm_axis.z * s) + ((norm_axis.x * norm_axis.y) * (1.0f - c));
  _transformation(0,2) = (norm_axis.y * s) + ((norm_axis.x * norm_axis.z) * (1.0f - c));
  _transformation(1,0) = (norm_axis.z * s) + ((norm_axis.x * norm_axis.y) * (1.0f - c));
  _transformation(1,1) = c + ((norm_axis.y * norm_axis.y) * (1.0f - c));
  _transformation(1,2) = -(norm_axis.x * s) + ((norm_axis.y * norm_axis.z) * (1.0f - c));
  _transformation(2,0) = -(norm_axis.y * s) + ((norm_axis.x * norm_axis.z) * (1.0f - c));
  _transformation(2,1) = (norm_axis.x * s) + ((norm_axis.y * norm_axis.z) * (1.0f - c));
  _transformation(2,2) = c + ((norm_axis.z * norm_axis.z) * (1.0f - c));

  _inverseTransformation = _transformation.transpose();
}


rotation3d::rotation3d(const rotation3d& r) : transformation3d(r)
{
  // Do Nothing
}
