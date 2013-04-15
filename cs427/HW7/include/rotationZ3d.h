#ifndef _ROTATIONZ3D_H_
#define _ROTATIONZ3D_H_

#include "transformation3d.h"

class rotationZ3d : public transformation3d {
 public:
  //////////////////
  // Constructors //
  //////////////////
  rotationZ3d(void);
  rotationZ3d(float angle);
  rotationZ3d(const rotationZ3d& r);
};

#endif /* _ROTATIONZ3D_H_ */
