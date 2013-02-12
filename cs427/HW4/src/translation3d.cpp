#include "translation3d.h"

//////////////////
// Constructors //
//////////////////
translation3d::translation3d(void) : transformation3d()
{
  // Do Nothing
}


translation3d::translation3d(const vec3d& translation) : transformation3d()
{
  // HW4: implement this
  //      return: nothing
  //      modifies: sets the member variables (defined in transformation3d) such that it represents a translation
  
  _translation = translation;
  _transformation = mat3d(1.0f);
}


translation3d::translation3d(const translation3d& t) : transformation3d(t)
{
  // Do Nothing
}
