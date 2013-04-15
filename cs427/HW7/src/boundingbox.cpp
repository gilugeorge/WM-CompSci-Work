#include "interval.h"
#include "constants.h"
#include "boundingbox.h"


/////////////////
// Constructor //
/////////////////
boundingBox::boundingBox(void)
{
  _lfb = vec3d(+LARGE);
  _rbt = vec3d(-LARGE);
}


boundingBox::boundingBox(const vec3d& lfb, const vec3d& rbt) 
{
  _lfb = lfb; 
  _rbt = rbt;

  // Make sure _lfb is always smaller (i.e., left front bottom) than _rbt.
  for(unsigned int i=0; i < 3; i++)
    if(_rbt[i] < _lfb[i]) std::swap(_rbt[i], _lfb[i]);
  
  // Done.
}


boundingBox::boundingBox(const boundingBox& bb)
{
  _lfb = bb._lfb;
  _rbt = bb._rbt;
}
  


///////////////
// Operators //
///////////////
boundingBox& boundingBox::operator=(const boundingBox& src) 
{ 
  _assign(src); 
  return *this; 
}


boundingBox& boundingBox::operator+=(const boundingBox& bb)
{
  // compute the union of two bounding boxes.
  for(unsigned int i=0; i < 3; i++)
  {
    if(_lfb[i] > bb._lfb[i]) _lfb[i] = bb._lfb[i];
    if(_rbt[i] < bb._rbt[i]) _rbt[i] = bb._rbt[i];
  }

  return *this;
}


boundingBox boundingBox::operator+(const boundingBox& bb) const
{
  boundingBox res(*this);
  res += bb;
  return res;
}



////////////////
// Inspectors //
////////////////
const vec3d& boundingBox::leftFrontBottom(void) const
{ 
  return _lfb; 
}


const vec3d& boundingBox::rightBackTop(void) const 
{ 
  return _rbt; 
}


vec3d boundingBox::size(void) const
{ 
  return _rbt - _lfb; 
}



/////////////
// Methods //
/////////////
void boundingBox::expand(const vec3d& p)
{
  // Move bounds if point lies outside.
  for(unsigned int i=0; i < 3; i++)
  {
    if(_lfb[i] > p[i]) _lfb[i] = p[i];
    if(_rbt[i] < p[i]) _rbt[i] = p[i];
  }
}


void boundingBox::expand(const vec3d& p, float border)
{
  // Move bounds if point lies outside. Move bounds to point + additional padding (border)
  for(unsigned int i=0; i < 3; i++)
  {
    if(_lfb[i] > p[i]-border) _lfb[i] = p[i]-border;
    if(_rbt[i] < p[i]+border) _rbt[i] = p[i]+border;
  }
}


void boundingBox::expand(float border)
{ 
  // expand the box by a border-margin.
  _lfb -= vec3d(border); 
  _rbt += vec3d(border); 
}


bool boundingBox::isIn(const vec3d& p) const
{
  return (_lfb.x < p.x && _lfb.y < p.y && _lfb.z < p.z &&
	  _rbt.x > p.x && _rbt.y > p.y && _rbt.z > p.z );
}


bool boundingBox::isHit(const ray& r) const
{
  // init
  interval boxInterval(0, +LARGE);

  // for every slab
  for(unsigned int i=0; i != 3; i++)
  {
    // compute the slab
    interval slab(_lfb[i], _rbt[i]);
    slab -= r.origin()[i];

    // check for the case where the ray is parallel to the slab
    if(fabs(r.direction()[i]) < EPSILON)
    {
      // if identical signs => no hit
      if((slab.lower() < 0.0f) == (slab.upper() < 0.0f))
	return false;

      // skip remainder to this iteration
      continue;
    }
    else
      slab /= r.direction()[i];

    // intersect
    boxInterval.intersect(slab);
    if(boxInterval.empty())
      return false;
  }

  // Done.
  return true;
}



/////////////////////
// Private Methods //
/////////////////////
void boundingBox::_swap(boundingBox& bb)
{
  std::swap(_lfb, bb._lfb);
  std::swap(_rbt, bb._rbt);
}


void boundingBox::_assign(const boundingBox& bb)
{
  // trivial case check
  if(this == &bb) return;

  // copy
  _lfb = bb._lfb;
  _rbt = bb._rbt;

  // Done.
}

 
