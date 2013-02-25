#include "reflectanceComponent.h"

/////////////////
// Constructor //
/////////////////
reflectanceComponent::reflectanceComponent(const albedo_base* albedo, const brdf_base* brdf)
{
  // NOTE: Only the pointer to the object is copied.
  //       The object is NOT cloned!  
  //       Thus, you need to ensure that the referred object remains alive.
  _albedo = albedo;
  _brdf = brdf;
}


reflectanceComponent::reflectanceComponent(const reflectanceComponent& rc)
{
  // NOTE: Only the pointer to the object is copied.
  //       The object is NOT cloned!  
  //       Thus, you need to ensure that the referred object remains alive.
  _albedo = rc._albedo;
  _brdf = rc._brdf;
}



///////////////
// Operators //
///////////////
reflectanceComponent& reflectanceComponent::operator=(const reflectanceComponent& rc)
{
  _assign(rc);
  return *this;
}



/////////////
// Methods //
/////////////
color reflectanceComponent::evaluate(const vec3d& in, const vec3d& normal, const vec3d& out, const vec2d& textureCoord) const
{
  return _albedo->evaluate(textureCoord) * _brdf->evaluate(in, normal, out);
}



/////////////////////
// Private Methods //
/////////////////////
void reflectanceComponent::_swap(reflectanceComponent& rc)
{
  std::swap(_albedo, rc._albedo);
  std::swap(_brdf, rc._brdf);
}


void reflectanceComponent::_assign(const reflectanceComponent& rc)
{
  _albedo = rc._albedo;
  _brdf = rc._brdf;
}
