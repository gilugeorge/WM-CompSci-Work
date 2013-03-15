#ifndef _CONSTANTALBEDO_H_
#define _CONSTANTALBEDO_H_

#include <ostream>

#include "color.h"
#include "vec2d.h"
#include "albedo_base.h"

class constantAlbedo : public albedo_base {
 public:
  /////////////////
  // Constructor //
  /////////////////
  constantAlbedo(const color& col=color(1.0f, 1.0f, 1.0f));
  constantAlbedo(const constantAlbedo& ca);

  //////////////
  // Operator //
  //////////////
  constantAlbedo& operator=(const constantAlbedo& ca);

  /////////////
  // Methods //
  /////////////
  virtual color evaluate(const vec2d& textureCoord) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(constantAlbedo& a, constantAlbedo& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const constantAlbedo& ca)
  {
    ca._print(s);
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(constantAlbedo& ca);
  void _assign(const constantAlbedo& ca);
  virtual void _print(std::ostream& s) const;

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  color _albedo;
};

#endif /* _CONSTANTALBEDO_H_ */
