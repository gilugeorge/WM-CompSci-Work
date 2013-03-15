#ifndef _ROTATIONY3D_H_
#define _ROTATIONY3D_H_

#include "transformation3d.h"

class rotationY3d : public transformation3d {
 public:
  //////////////////
  // Constructors //
  //////////////////
  rotationY3d(void);
  rotationY3d(float angle);
  rotationY3d(const rotationY3d& r);
};

#endif /* _ROTATIONY3D_H_ */
