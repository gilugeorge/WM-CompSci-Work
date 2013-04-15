#include "sphericalTextureProjection.h"

#include <cmath>

//////////////////
// Constructors //
//////////////////
sphericalTextureProjection::sphericalTextureProjection(void) : textureProjection_base()
{
  // Do nothing
}


sphericalTextureProjection::sphericalTextureProjection(const transformation3d& t) : textureProjection_base(t)
{
  // Do nothing
}


sphericalTextureProjection::sphericalTextureProjection(const sphericalTextureProjection& stp) : textureProjection_base(stp)
{
  // Do nothing
}



///////////////
// Operators //
///////////////
sphericalTextureProjection& sphericalTextureProjection::operator=(const sphericalTextureProjection& stp)
{
  _assign(stp);
  return *this;
}



///////////////////////
// Protected Methods //
///////////////////////
void sphericalTextureProjection::_assign(const sphericalTextureProjection& stp)
{
  textureProjection_base::_assign(stp);
}


void sphericalTextureProjection::_swap(sphericalTextureProjection& stp)
{
  textureProjection_base::_swap(stp);
}


void sphericalTextureProjection::_print(std::ostream& s) const
{
  s << "Spherical Texture Projection: " << _transformation;
}


vec2d sphericalTextureProjection::computeTextureCoordinate(const vec3d& v) const
{
  // normalize
  vec3d n = v.normalize();

  // compute (theta,phi)
  vec2d thetaPhi(atan2(n.y, n.x), acos(n.z));

  // map to [0,1]
  if(thetaPhi.u < 0.0f) thetaPhi.u += (2.0f * M_PI);
  thetaPhi /= vec2d(2.0f * M_PI, M_PI);

  // Done.
  return thetaPhi;
}
