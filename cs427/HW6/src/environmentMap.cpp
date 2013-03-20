#include "environmentMap.h"

//////////////////
// Constructors //
//////////////////
environmentMap::environmentMap(const std::string& textureName, const transformation3d& transformation)
{
  _texture.load(textureName);
  _transformation = transformation;
}


environmentMap::environmentMap(const environmentMap& em)
{
  _texture = em._texture;
  _transformation = em._transformation;
}


  
//////////////
// Operator //
//////////////
environmentMap& environmentMap::operator=(const environmentMap& em)
{
  _assign(em);
  return *this;
}



/////////////
// Methods //
/////////////
color environmentMap::evaluate(const ray& r) const
{
  // HW6: implement this
  //      returns: the color in the environment in direction r.  You can see the environment as an infinitely 
  //               large sphere that sits around the scene (and which reflects light inwards).  You should use
  //               the normal theta-phi encoding of direction to texture coordinate.
  //      modifies: nothing
  
    // normalize
  vec3d n = r.direction().normalize();

  // compute (theta,phi)
  vec3d thetaPhi(atan2(n.y, n.x), acos(n.z), 0.0f);

  // map to [0,1]
  if(thetaPhi.x < 0.0f) thetaPhi.x += (2.0f * M_PI);
  thetaPhi /= vec3d(2.0f * M_PI, M_PI,0.0f);

  // Done.
  return _texture(thetaPhi.x, thetaPhi.y);
  return color(0.0f, 0.0f, 0.0f);
}



/////////////////////
// Private Methods //
/////////////////////
void environmentMap::_swap(environmentMap& em)
{
  std::swap(_texture, em._texture);
  std::swap(_transformation, em._transformation);
}


void environmentMap::_assign(const environmentMap& em)
{
  // sanity check
  if(this == &em) return;

  // copy
  environmentMap temp(em);
  _swap(temp);

  // Done.
}
