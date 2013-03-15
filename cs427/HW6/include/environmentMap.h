#ifndef _ENVIRONMENTMAP_H_
#define _ENVIRONMENTMAP_H_

#include <string>
#include <ostream>

#include "ray.h"
#include "color.h"
#include "image.h"
#include "transformation3d.h"

class environmentMap {
 public:
  //////////////////
  // Constructors //
  //////////////////
  environmentMap(const std::string& textureName, const transformation3d& transformation=transformation3d());
  environmentMap(const environmentMap& em);
  
  //////////////
  // Operator //
  //////////////
  environmentMap& operator=(const environmentMap& em);

  /////////////
  // Methods //
  /////////////
  color evaluate(const ray& r) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(environmentMap& a, environmentMap& b) { a._swap(b); }
  
  friend std::ostream& operator<<(std::ostream& s, const environmentMap& em)
  {
    s << "Environment Map (" << em._texture.width() << "x" << em._texture.height() << "), " << em._transformation;
    return s;
  }
  
 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(environmentMap& em);
  void _assign(const environmentMap& em);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  transformation3d _transformation;
  image _texture;
};

#endif /* _ENVIRONMENTMAP_H_ */
