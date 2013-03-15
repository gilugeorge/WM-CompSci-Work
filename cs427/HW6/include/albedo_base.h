#ifndef _ALBEDO_BASE_H_
#define _ALBEDO_BASE_H_

#include <ostream>

#include "vec2d.h"
#include "color.h"

////////////////////////////////////
// Abstract base class for albedo //
////////////////////////////////////
class albedo_base {
 public:
  /////////////
  // Methods //
  /////////////
  virtual color evaluate(const vec2d& textureCoord) const = 0;

  /////////////
  // Friends //
  /////////////
  friend std::ostream& operator<<(std::ostream& s, const albedo_base& a)
  {
    a._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  virtual void _print(std::ostream& s) const = 0;
};

#endif /* _ALBEDO_BASE_H_ */

