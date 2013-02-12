#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <ostream>

#include "color.h"

class image {
 public:
  //////////////
  // Typedefs //
  //////////////
  typedef color               value_type;
  typedef value_type&         reference;
  typedef const value_type&   const_reference;
  typedef value_type*         iterator;
  typedef const value_type*   const_iterator;
  typedef size_t              difference_type;
  typedef size_t              size_type;

  //////////////////
  // Constructors //
  //////////////////
  image(size_type width=0, size_type height=0);
  image(size_type width, size_type height, const_reference col);
  image(const std::string& filename);
  image(const image& src);

  /////////////////
  // Destructors //
  /////////////////
  ~image(void);

  ////////////////
  // Inspectors //
  ////////////////
  iterator begin(void);
  const_iterator begin(void) const;
  
  iterator end(void);
  const_iterator end(void) const;

  reference operator()(size_type x, size_type y);
  const_reference operator()(size_type x, size_type y) const;

  size_type size(void) const;
  size_type width(void) const;
  size_type height(void) const;

  //////////////
  // Mutators //
  //////////////
  void resize(size_type newWidth, size_type newHeight);
  
  void fill(const_reference col);
  void clear(void) { fill(color(0)); }

  /////////////
  // Methods //
  /////////////
  void save(const std::string& filename) const;
  void load(const std::string& filename);

  ///////////////
  // Operators //
  ///////////////
  image& operator=(const image& src);

  image operator+(const image& img) const;
  image operator-(const image& img) const;
  image operator*(const image& img) const;
  image operator*(const_reference col) const;
  image operator*(float scale) const;
  image operator/(const image& img) const;
  image operator/(const_reference col) const;
  image operator/(float scale) const;

  image& operator+=(const image& img);
  image& operator-=(const image& img);
  image& operator*=(const image& img);
  image& operator*=(const_reference col);
  image& operator*=(float scale);
  image& operator/=(const image& img);
  image& operator/=(const_reference col);
  image& operator/=(float scale);

  /////////////
  // Friends //
  /////////////
  friend void swap(image& a, image& b) { a._swap(b); }
 
  friend image operator*(float scale, const image& img) { return (img * scale); }
  friend image operator*(const_reference col, const image& img) { return (img * col); }

  friend std::ostream& operator<<(std::ostream& s, const image& img)
  {
    s << "Image: (" << img.width() << ", " << img.height() << ")";
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _alloc(size_type width, size_type height);
  void _dealloc(void);
  void _swap(image& swp);
  void _assign(const image& src);
  reference _at(size_type x, size_type y);
  const_reference _at(size_type x, size_type y) const;

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  size_t _width, _height;
  color *_data;
};

#endif /* _IMAGE_H_ */
