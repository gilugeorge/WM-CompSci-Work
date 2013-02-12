#ifndef _MAT2D_H_
#define _MAT2D_H_

#include <ostream>

#include "vec2d.h"

class mat2d {
 public:
  /////////////
  // Typedef //
  /////////////
  typedef float               value_type;
  typedef value_type&         reference;
  typedef const value_type&   const_reference;
  typedef value_type*         iterator;
  typedef const value_type*   const_iterator;
  typedef std::size_t         difference;
  typedef std::size_t         size_type;

  /////////////////
  // Constructor //
  /////////////////
  mat2d(void);                              // all elements are set to 0
  explicit mat2d(value_type diag);          // all elements are set to 0, the diagonal elements are set to 'diag'
  mat2d(const vec2d& X, const vec2d& Y);    // the columns are set to X and Y.
  mat2d(const mat2d& m);                    // copy constructor

  ////////////////
  // Destructor //
  ////////////////
  ~mat2d(void) {}

  ////////////////
  // Inspectors //
  ////////////////
  size_type width(void) const  { return 2; }
  size_type height(void) const { return 2; }
  size_type size(void) const   { return 4; }

  iterator begin(void);
  const_iterator begin(void) const;

  iterator end(void);
  const_iterator end(void) const;

  reference operator()(size_type row, size_type col);
  const_reference operator()(size_type row, size_type col) const;

  vec2d row(size_type row) const;
  vec2d column(size_type col) const;

  //////////////
  // Mutators //
  //////////////
  void clear(value_type value=0.0f);
  void identity(value_type diag=1.0f);

  void set(const vec2d& X, const vec2d& Y);
  void setDiagonal(value_type d);
  void setDiagonal(const vec2d& d);

  void setRow(const vec2d& v, size_type row);
  void setColumn(const vec2d& v, size_type col);

  mat2d transpose(void) const;

  ///////////////
  // Operators //
  ///////////////
  mat2d operator=(const mat2d& m);

  mat2d operator+(const mat2d& m) const;
  mat2d operator-(const mat2d& m) const;
  mat2d operator*(const mat2d& m) const;
  vec2d operator*(const vec2d& v) const;
  mat2d operator*(value_type scale) const;
  mat2d operator/(value_type scale) const;

  mat2d& operator+=(const mat2d& m);
  mat2d& operator-=(const mat2d& m);
  mat2d& operator*=(const mat2d& m);
  mat2d& operator*=(value_type scale);
  mat2d& operator/=(value_type scale);
  
  /////////////
  // Friends //
  /////////////
  friend void swap(mat2d& a, mat2d& b) { a._swap(b); }

  friend vec2d operator*(const vec2d& v, const mat2d& m)   { return m._premultiply(v); }
  friend mat2d operator*(value_type scale, const mat2d& m) { return (m * scale); }

  friend void transpose(mat2d& m) { std::swap(m._data[1], m._data[2]);  }

  friend std::ostream& operator<<(std::ostream& s, const mat2d& m)
  {
    s << "[[" << m(0,0) << ", " << m(0,1) << "],[" << m(1,0) << ", " << m(1,1) << "]]";
    return s;
  }
  
 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(mat2d& m);
  void _assign(const mat2d& m);

  reference _at(size_type row, size_type col);
  const_reference _at(size_type row, size_type col) const;

  vec2d _premultiply(const vec2d& v) const;

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  value_type _data[4];
};

#endif /* _MAT2D_H_ */

