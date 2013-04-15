#include "texturedAlbedo.h"


/////////////////
// Constructor //
/////////////////
texturedAlbedo::texturedAlbedo(const std::string& textureName)
{
  _texture.load(textureName);
}


texturedAlbedo::texturedAlbedo(const texturedAlbedo& ta)
{
  _texture = ta._texture;
}



//////////////
// Operator //
//////////////
texturedAlbedo& texturedAlbedo::operator=(const texturedAlbedo& ta)
{
  _assign(ta);
  return *this;
}



/////////////
// Methods //
/////////////
color texturedAlbedo::evaluate(const vec2d& textureCoord) const
{
  // get pixel coord map to the nearest edge if outside
  signed int u= textureCoord.u * _texture.width();
  signed int v= textureCoord.v * _texture.height();

  if(u < 0) u = 0.0f;
  else if(u > _texture.width() - 1) u = _texture.width() - 1;

  if(v < 0) v = 0.0f;
  else if(v > _texture.height() - 1) v = _texture.height() - 1;


  // Done.
  return _texture(u,v);
}



/////////////////////
// Private Methods //
/////////////////////
void texturedAlbedo::_swap(texturedAlbedo& ta)
{
  std::swap(_texture, ta._texture);
}


void texturedAlbedo::_assign(const texturedAlbedo& ta)
{
  _texture = ta._texture;
}


void texturedAlbedo::_print(std::ostream& s) const
{
  s << "Texture Albedo: (" << _texture.width() << "x" << _texture.height() << ")";
}
