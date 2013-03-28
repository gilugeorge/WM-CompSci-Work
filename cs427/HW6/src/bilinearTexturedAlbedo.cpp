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
  
  //used wikipedia structure as template for this
	int x = floor(textureCoord.u);
	int y = floor(textureCoord.v);
	double u_ratio = textureCoord.u - x;
	double v_ratio = textureCoord.v - y;
	double u_opposite = 1 - u_ratio;
	double v_opposite = 1 - v_ratio;
	color result = (color) (_texture(x,y)   * u_opposite  + _texture(x+1,y)   * u_ratio) * v_opposite + 
		           (_texture(x,y+1) * u_opposite  + _texture(x+1,y+1) * u_ratio) * v_ratio;
	return result;
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
