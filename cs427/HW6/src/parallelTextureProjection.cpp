#include "parallelTextureProjection.h"

#include <cmath>

//////////////////
// Constructors //
//////////////////
parallelTextureProjection::parallelTextureProjection(void) : textureProjection_base()
{
  // Do nothing
}


parallelTextureProjection::parallelTextureProjection(const transformation3d& t) : textureProjection_base(t)
{
  // Do nothing
}


parallelTextureProjection::parallelTextureProjection(const parallelTextureProjection& ptp) : textureProjection_base(ptp)
{
  // Do nothing
}



///////////////
// Operators //
///////////////
parallelTextureProjection& parallelTextureProjection::operator=(const parallelTextureProjection& ptp)
{
  _assign(ptp);
  return *this;
}



///////////////////////
// Protected Methods //
///////////////////////
void parallelTextureProjection::_assign(const parallelTextureProjection& ptp)
{
  textureProjection_base::_assign(ptp);
}


void parallelTextureProjection::_swap(parallelTextureProjection& ptp)
{
  textureProjection_base::_swap(ptp);
}


void parallelTextureProjection::_print(std::ostream& s) const
{
  s << "Parallel Texture Projection: " << _transformation;
}


vec2d parallelTextureProjection::computeTextureCoordinate(const vec3d& v) const
{
  // Done.
  return vec2d(v.x, v.y);
}
