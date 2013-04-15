#include "bilinearTexturedAlbedo.h"


/////////////////
// Constructor //
/////////////////
bilinearTexturedAlbedo::bilinearTexturedAlbedo(const std::string& textureName)
{
  _texture.load(textureName);
}


bilinearTexturedAlbedo::bilinearTexturedAlbedo(const bilinearTexturedAlbedo& bta)
{
  _texture = bta._texture;
}



//////////////
// Operator //
//////////////
bilinearTexturedAlbedo& bilinearTexturedAlbedo::operator=(const bilinearTexturedAlbedo& bta)
{
  _assign(bta);
  return *this;
}



/////////////
// Methods //
/////////////
color bilinearTexturedAlbedo::evaluate(const vec2d& textureCoord) const
{
  // get texel coordinate
  float texelU = std::min(textureCoord.u * (_texture.width()-1), (float)(_texture.width()-1));
  float texelV = std::min(textureCoord.v * (_texture.height()-1), (float)(_texture.height()-1));

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
void bilinearTexturedAlbedo::_swap(bilinearTexturedAlbedo& bta)
{
  std::swap(_texture, bta._texture);
}


void bilinearTexturedAlbedo::_assign(const bilinearTexturedAlbedo& bta)
{
  _texture = bta._texture;
}


void bilinearTexturedAlbedo::_print(std::ostream& s) const
{
  s << "Bilinear Texture Albedo: (" << _texture.width() << "x" << _texture.height() << ")";
}
