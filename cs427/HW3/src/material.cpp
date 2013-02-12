#include "material.h"

/////////////////
// Constructor //
/////////////////
material::material(void)
{
  // do nothing
}


material::material(const reflectanceComponent& rf)
{
  addComponent(rf);
}


material::material(const material& m)
{
  _components = m._components;
}



//////////////
// Operator //
//////////////
material& material::operator=(const material& m)
{
  _assign(m);
  return *this;
}



//////////////
// Mutators //
//////////////
void material::addComponent(const reflectanceComponent& rf)
{
  _components.push_back(rf);
}



/////////////
// Methods //
/////////////
color material::evaluate(const vec3d& in, const vec3d& normal, const vec3d& out, const vec2d& textureCoord) const
{
  color result;

  // cycle through each component, and add the contributions
  for(std::vector<reflectanceComponent>::const_iterator itr = _components.begin(); itr != _components.end(); itr++)
    result += itr->evaluate(in, normal, out, textureCoord);

  // Done.
  return result;
}



/////////////////////
// Private Methods //
/////////////////////
void material::_swap(material& m)
{
  std::swap(_components, m._components);
}


void material::_assign(const material& m)
{
  // avoid trivial case => self-assignment
  if(&m == this) return;

  // create copy & assign
  material copy(m);
  _swap(copy);

  // Done.
}
