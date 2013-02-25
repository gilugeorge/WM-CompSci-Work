#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <vector>
#include <ostream>

#include "vec2d.h"
#include "vec3d.h"
#include "color.h"
#include "reflectanceComponent.h"

class material {
 public:
  /////////////////
  // Constructor //
  /////////////////
  material(void);
  material(const reflectanceComponent& rf);
  material(const material& m);

  //////////////
  // Operator //
  //////////////
  material& operator=(const material& m);

  //////////////
  // Mutators //
  //////////////
  void addComponent(const reflectanceComponent& rf);

  /////////////
  // Methods //
  /////////////
  color evaluate(const vec3d& in, const vec3d& normal, const vec3d& out, const vec2d& textureCoord) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(material& a, material& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const material& m)
  {
    s << "Material: ";
    for(std::vector<reflectanceComponent>::const_iterator itr = m._components.begin(); itr != m._components.end(); itr++)
    {
      s << *itr;
      if(itr+1 != m._components.end()) s << ", ";
    }
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(material& m);
  void _assign(const material& m);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  std::vector<reflectanceComponent> _components;
};

#endif /* _MATERIAL_H_ */
