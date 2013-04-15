#ifndef _BILINEARTEXTUREDALBEDO_H_
#define _BILINEARTEXTUREDALBEDO_H_

#include <string>
#include <ostream>

#include "color.h"
#include "vec2d.h"
#include "image.h"
#include "albedo_base.h"

class bilinearTexturedAlbedo : public albedo_base {
 public:
  /////////////////
  // Constructor //
  /////////////////
  bilinearTexturedAlbedo(const std::string& textureName);
  bilinearTexturedAlbedo(const bilinearTexturedAlbedo& bta);

  //////////////
  // Operator //
  //////////////
  bilinearTexturedAlbedo& operator=(const bilinearTexturedAlbedo& bta);

  /////////////
  // Methods //
  /////////////
  virtual color evaluate(const vec2d& textureCoord) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(bilinearTexturedAlbedo& a, bilinearTexturedAlbedo& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const bilinearTexturedAlbedo& bta)
  {
    bta._print(s);
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(bilinearTexturedAlbedo& bta);
  void _assign(const bilinearTexturedAlbedo& bta);
  virtual void _print(std::ostream& s) const;

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  image _texture;
};

#endif /* _BILINEARTEXTUREDALBEDO_H_ */
