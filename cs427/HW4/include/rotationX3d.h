#ifndef _ROTATIONX3D_H_
#define _ROTATIONX3D_H_

#include "transformation3d.h"

class rotationX3d : public transformation3d {
 public:
  //////////////////
  // Constructors //
  //////////////////
  rotationX3d(void);
  rotationX3d(float angle);
  rotationX3d(const rotationX3d& r);
};

#endif /* _ROTATIONX3D_H_ */
