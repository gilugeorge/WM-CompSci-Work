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
  // HW5: implement this
  //      returns: the color at 'textureCoord' in _texture.  Note, textureCoord is given in a resolution independent range.
  //               You will need to scale it such that [0,1]x[0,1] it maps to [0,width-1]x[0,height-1].  Coordinates outside this
  //               range should be mapped to the nearest coordinate inside [0,1]x[0,1] before converting to [0,width-1]x[0,height-1] 
  //      modifies: nothing.
  vec2d coord = textureCoord;
  
	if( coord[0] <= 0 ){
		coord[0] = 0.0f;
	}else if( coord[0] >= 1 ){
		coord[0] = 1.0f;
	}
	if( coord[1] <= 0 ){
		coord[1] = 0.0f;
	}else if( coord[1] >= 1 ){
		coord[1] = 1.0f;
	}
	
	coord[0] = coord[0] * (_texture.width()-1.0f);
	coord[1] = coord[1] * (_texture.height()-1.0f);
	
	//make it more precise by rounding up or down.
	if(coord[0] -	floor(coord[0]) < 0.5f){
		coord[0] = floor(coord[0]);
	}else{
		coord[0] = (coord[0]) + 1.0f;
	}
	if(coord[1] -	floor(coord[1]) < 0.5f){
		coord[1] = floor(coord[1]);
	}else{
		coord[1] = floor(coord[1]) + 1.0f;
	}
	
	return _texture(coord[0], coord[1]);
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
