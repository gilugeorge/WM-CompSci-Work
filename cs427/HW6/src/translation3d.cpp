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
  _translation = translation;
}


translation3d::translation3d(const translation3d& t) : transformation3d(t)
{
  // Do Nothing
}
