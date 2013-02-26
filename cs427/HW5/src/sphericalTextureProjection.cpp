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
  // HW5: Implement this.
  //      returns: the spherical coordinate (phi, theta) of v projected onto a unit sphere.
  //      modifies: nothing.
  v.normalize();
  float theta, phi;

  theta = acos(v.z)/M_PI;
  if(v.y >= 0){
	  phi = acos(v.x/(sin(M_PI*theta)))/ (2*M_PI);
	}else{
		phi = (M_PI + acos(v.x/(sin(M_PI*theta)))) / (2*M_PI);
	}  
  
  return vec2d(phi,theta);
}
