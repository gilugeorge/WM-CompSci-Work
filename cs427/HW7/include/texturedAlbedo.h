#ifndef _TEXTUREDALBEDO_H_
#define _TEXTUREDALBEDO_H_

#include <string>
#include <ostream>

#include "color.h"
#include "vec2d.h"
#include "image.h"
#include "albedo_base.h"

class texturedAlbedo : public albedo_base {
 public:
  /////////////////
  // Constructor //
  /////////////////
  texturedAlbedo(const std::string& textureName);
  texturedAlbedo(const texturedAlbedo& ta);

  //////////////
  // Operator //
  //////////////
  texturedAlbedo& operator=(const texturedAlbedo& ta);

  /////////////
  // Methods //
  /////////////
  virtual color evaluate(const vec2d& textureCoord) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(texturedAlbedo& a, texturedAlbedo& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const texturedAlbedo& ta)
  {
    ta._print(s);
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(texturedAlbedo& ta);
  void _assign(const texturedAlbedo& ta);
  virtual void _print(std::ostream& s) const;

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  image _texture;
};

#endif /* _TEXTUREDALBEDO_H_ */
