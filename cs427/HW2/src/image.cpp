#include <fstream>
#include <cassert>
#include <algorithm>
#include <functional>

#include "image.h"
#include "customException.h"


//////////////////
// Constructors //
//////////////////
image::image(image::size_type width, image::size_type height)
{
  _alloc(width, height);
}


image::image(image::size_type width, image::size_type height, image::const_reference col)
{
  _alloc(width, height);
  std::fill(begin(), end(), col);
}


image::image(const std::string& filename)
{
  _data = NULL;
  _width = 0;
  _height = 0;
  load(filename);
}

image::image(const image& src)
{
  _alloc(src.width(), src.height());
  std::copy(src.begin(), src.end(), begin());
}



/////////////////
// Destructors //
/////////////////
image::~image(void)
{
  _dealloc();
}


////////////////
// Inspectors //
////////////////
image::iterator image::begin(void)
{
  return &(_data[0]);
}


image::const_iterator image::begin(void) const
{
  return &(_data[0]);
}
  

image::iterator image::end(void)
{
  return &(_data[size()]);
}


image::const_iterator image::end(void) const
{
  return &(_data[size()]);
}


image::reference image::operator()(image::size_type x, image::size_type y)
{
  assert(x < width() && y < height());
  return _at(x,y);
}


image::const_reference image::operator()(image::size_type x, image::size_type y) const
{
  assert(x < width() && y < height());
  return _at(x,y);
}


image::size_type image::size(void) const
{
  return (width() * height());
}


image::size_type image::width(void) const
{
  return _width;
}


image::size_type image::height(void) const
{
  return _height;
}



//////////////
// Mutators //
//////////////
void image::resize(image::size_type newWidth, image::size_type newHeight)
{
  // check if new size == old size
  if(width() == newWidth && height() == newHeight)
    return;

  // dealloc and re-alloc
  _dealloc();
  _alloc(newWidth, newHeight);

  // Done.
}
  

void image::fill(image::const_reference col)
{
  std::fill(begin(), end(), col);
}



/////////////
// Methods //
/////////////
void image::save(const std::string& filename) const
{
  // sanity check
  assert(width() != 0 && height() != 0);

  // open file
  std::ofstream ofs(filename.c_str());
  if(!ofs.is_open()) throw customException(std::string("Unable to open file: ") + filename);

  // write header
  ofs << "P6\n" << width() << " " << height() << "\n" << "255\n";

  // convert to char buffer
  unsigned char *buffer = new unsigned char[size() * 3], *bufItr = buffer;
  for(image::const_iterator imgItr = begin(); imgItr != end(); imgItr++)
  {
    // clamp color to [0..1] range
    color clamped(*imgItr);
    clamped.clamp(0.0f, 1.0f);
    
    // copy into char buffer
    for(unsigned int channel=0; channel < 3; channel++, bufItr++)
      *bufItr = (unsigned char)(clamped[channel] * 255.0f);
  }
    
  // write body
  ofs.write((const char*)(buffer), size() * 3);

  // Done.
  delete[] buffer;
}


void image::load(const std::string& filename)
{
  // open file
  std::ifstream ifs(filename.c_str());
  if(!ifs.is_open()) throw customException(std::string("Unable to open file: ") + filename);

  // header header
  char dummy;
  std::string strBuffer;
  size_type newWidth, newHeight;
  
  // => read magic number "P6". Take care to read trailing '\n'
  ifs >> strBuffer;
  ifs.get();
  if(strBuffer != "P6") throw customException("Not a valid PPM image file");

  // => skip comments (starting with '#')
  while(!ifs.eof() && ifs.peek() == '#') 
    while(ifs.get() != '\n' && !ifs.eof());
  
  // => read width and height. Take care to read trailing '\n'
  ifs >> newWidth >> newHeight;
  ifs.get();
  assert(!ifs.eof());

  // => skip comments
  while(!ifs.eof() && ifs.peek() == '#') 
    while(ifs.get() != '\n' && !ifs.eof());

  // => check magic number '255\n'
  assert(ifs.get() == '2' && ifs.get() == '5' && ifs.get() == '5' && ifs.get() == '\n' && !ifs.eof());

  // allocate memory
  resize(newWidth, newHeight);

  // read char buffer
  unsigned char *buffer = new unsigned char[size() * 3], *bufItr = buffer;
  ifs.read((char*)(buffer), size() * 3);

  // convert char buffer to image
  for(image::iterator imgItr = begin(); imgItr != end(); imgItr++)
    for(unsigned int channel=0; channel < 3 ; channel++, bufItr++)
      (*imgItr)[channel] = (float)(*bufItr) / 255.0f;

  // Done.
  delete[] buffer;
}



///////////////
// Operators //
///////////////
image& image::operator=(const image& src)
{
  _assign(src);
  return *this;
}


image image::operator+(const image& img) const
{
  // sanity check
  assert(width() == img.width() && height() == img.height());

  // create result
  image result(width(), height());
  std::transform(begin(), end(), img.begin(), result.begin(), std::plus<color>());

  // Done.
  return result;
}


image image::operator-(const image& img) const
{
  // sanity check
  assert(width() == img.width() && height() == img.height());

  // create result
  image result(width(), height());
  std::transform(begin(), end(), img.begin(), result.begin(), std::minus<color>());

  // Done.
  return result;
}


image image::operator*(const image& img) const
{
  // sanity check
  assert(width() == img.width() && height() == img.height());

  // create result
  image result(width(), height());
  std::transform(begin(), end(), img.begin(), result.begin(), std::multiplies<color>());

  // Done.
  return result;
}


image image::operator*(image::const_reference col) const
{
  // create result
  image result(width(), height());
  std::transform(begin(), end(), result.begin(), std::bind2nd(std::multiplies<color>(), col));

  // Done.
  return result;
}


image image::operator*(float scale) const
{
  return (*this * color(scale));
}


image image::operator/(const image& img) const
{
  // sanity check
  assert(width() == img.width() && height() == img.height());

  // create result
  image result(width(), height());
  std::transform(begin(), end(), img.begin(), result.begin(), std::divides<color>());

  // Done.
  return result;
}


image image::operator/(image::const_reference col) const
{
  // create result
  image result(width(), height());
  std::transform(begin(), end(), result.begin(), std::bind2nd(std::divides<color>(), col));

  // Done.
  return result;
}


image image::operator/(float scale) const
{
  return (*this / color(scale));
}


image& image::operator+=(const image& img)
{
  // sanity check
  assert(width() == img.width() && height() == img.height());

  // create result
  std::transform(begin(), end(), img.begin(), begin(), std::plus<color>());

  // Done.
  return *this;
}


image& image::operator-=(const image& img)
{
  // sanity check
  assert(width() == img.width() && height() == img.height());

  // create result
  std::transform(begin(), end(), img.begin(), begin(), std::minus<color>());

  // Done.
  return *this;
}


image& image::operator*=(const image& img)
{
  // sanity check
  assert(width() == img.width() && height() == img.height());

  // create result
  std::transform(begin(), end(), img.begin(), begin(), std::multiplies<color>());

  // Done.
  return *this;
}


image& image::operator*=(image::const_reference col)
{
  // create result
  std::transform(begin(), end(), begin(), std::bind2nd(std::multiplies<color>(), col));

  // Done.
  return *this;
}


image& image::operator*=(float scale)
{
  *this *= color(scale);
  return *this;
}


image& image::operator/=(const image& img)
{
  // sanity check
  assert(width() == img.width() && height() == img.height());

  // create result
  std::transform(begin(), end(), img.begin(), begin(), std::divides<color>());

  // Done.
  return *this;
}


image& image::operator/=(image::const_reference col)
{
  // create result
  std::transform(begin(), end(), begin(), std::bind2nd(std::divides<color>(), col));

  // Done.
  return *this;
}


image& image::operator/=(float scale)
{
  *this /= color(scale);
  return *this;
}



/////////////////////
// Private Methods //
/////////////////////
void image::_alloc(image::size_type width, image::size_type height)
{
  _data = NULL;
  _width = width;
  _height = height;

  if(_width != 0 && _height != 0)
    _data = new color[_width * _height];
}


void image::_dealloc(void)
{
  if(_data != NULL)
    delete[] _data;

  _data = NULL;
  _width = 0;
  _height = 0;
}


void image::_swap(image& swp)
{
  std::swap(_data, swp._data);
  std::swap(_width, swp._width);
  std::swap(_height, swp._height);
}


void image::_assign(const image& src)
{
  // sanity check
  if(this == &src) return;

  // copy
  image temp(src);
  _swap(temp);

  // Done.
}


image::reference image::_at(image::size_type x, image::size_type y)
{
  // row-major storage.
  return _data[ y * _width + x];
}


image::const_reference image::_at(image::size_type x, image::size_type y) const
{
  // row-major storage.
  return _data[ y * _width + x];
}
