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
  // inverse transform the ray
  ray transformedRay(r);
  transformedRay.inverseTransform(_transformation);

  // convert ray direction to texture coordinate
  float theta = acos(transformedRay.direction().z);
  float phi = atan2(transformedRay.direction().y, transformedRay.direction().x);

  if(phi < 0.0f) phi += 2.0f * M_PI;

  theta /= M_PI;
  phi /= 2.0f * M_PI;

  // get texel coordinate
  float texelU = std::min(phi * (_texture.width()-1), (float)(_texture.width()-1));
  float texelV = std::min(theta * (_texture.height()-1), (float)(_texture.height()-1));

  // compute corners
  float left = floor(texelU);
  float right = ceil(texelU);
  float top = floor(texelV);
  float bottom = ceil(texelV);

  // linear interpolate along X
  float w = texelU - left;
  color topColor = _texture(left,top)*(1.0f-w) + _texture(right,top)*w;
  color bottomColor = _texture(left,bottom)*(1.0f-w) + _texture(right,bottom)*w;

  // linear interlate along Y
  w = texelV - top;
  return (1.0f - w)*topColor + w*bottomColor;
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
