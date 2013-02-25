#ifndef _SCALE3D_H_
#define _SCALE3D_H_

#include "transformation3d.h"

class scale3d : public transformation3d {
 public:
  //////////////////
  // Constructors //
  //////////////////
  scale3d(void);
  scale3d(float uniformScale);
  scale3d(float scaleX, float scaleY, float scaleZ);
  scale3d(const scale3d& s);
};

#endif /* _SCALE3D_H_ */
