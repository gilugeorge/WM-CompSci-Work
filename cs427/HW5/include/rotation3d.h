#ifndef _ROTATION3D_H_
#define _ROTATION3D_H_

#include "transformation3d.h"

class rotation3d : public transformation3d {
 public:
  //////////////////
  // Constructors //
  //////////////////
  rotation3d(void);
  rotation3d(float angle, const vec3d& axis);
  rotation3d(const rotation3d& r);
};

#endif /* _ROTATION3D_H_ */
