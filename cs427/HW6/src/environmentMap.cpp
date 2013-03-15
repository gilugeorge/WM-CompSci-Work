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
