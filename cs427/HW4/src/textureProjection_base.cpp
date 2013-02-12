#include "textureProjection_base.h"

//////////////////
// Constructors //
//////////////////
textureProjection_base::textureProjection_base(void)
{
  // Do nothing
}


textureProjection_base::textureProjection_base(const transformation3d& t)
{
  _transformation = t;
}


textureProjection_base::textureProjection_base(const textureProjection_base& tp)
{
  _transformation = tp._transformation;
}



/////////////
// Methods //
////////////
void textureProjection_base::apply(triangle& t) const
{
  // copy and transform the triangle
  triangle tempTriangle(t);
  tempTriangle.transform(_transformation);

  // comput the text coordinate for each pixel
  vec2d textureCoord[3];
  for(unsigned int i=0; i < 3; i++)
    textureCoord[i] = computeTextureCoordinate( tempTriangle.vertex(i) );

  // update triangle
  t.setTextureCoordinates(textureCoord[0], textureCoord[1], textureCoord[2]);

  // Done.
}



///////////////////////
// Protected Methods //
///////////////////////
void textureProjection_base::_assign(const textureProjection_base& tp)
{
  _transformation = tp._transformation;
}


void textureProjection_base::_swap(textureProjection_base& tp)
{
  std::swap(_transformation, tp._transformation);
}
