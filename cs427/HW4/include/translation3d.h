#ifndef _TRANSLATION3D_H_
#define _TRANSLATION3D_H_

#include "transformation3d.h"

class translation3d : public transformation3d {
 public:
  //////////////////
  // Constructors //
  //////////////////
  translation3d(void);
  translation3d(const vec3d& translation);
  translation3d(const translation3d& t);
};

#endif /* _TRANSLATION3d_H_ */
