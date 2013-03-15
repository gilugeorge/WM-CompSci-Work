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
  // HW6: Implement this.
  //      Exactly the same as texturedAlbedo, but it now return the bilinearly interpolated texel color.
  return color(0.0f, 0.0f, 0.0f);
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
