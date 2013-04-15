#ifndef _MAT3D_H_
#define _MAT3D_H_

#include <ostream>

#include "vec3d.h"

class mat3d {
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
  mat3d(void);                                              // all elements are set to 0
  explicit mat3d(value_type diag);                          // all elements are set to 0, the diagonal elements are set to 'diag'
  mat3d(const vec3d& X, const vec3d& Y, const vec3d& Z);    // the columns are set to X and Y.
  mat3d(const mat3d& m);                                    // copy constructor

  ////////////////
  // Destructor //
  ////////////////
  ~mat3d(void) {}

  ////////////////
  // Inspectors //
  ////////////////
  size_type width(void) const  { return 3; }
  size_type height(void) const { return 3; }
  size_type size(void) const   { return 9; }

  iterator begin(void);
  const_iterator begin(void) const;

  iterator end(void);
  const_iterator end(void) const;

  reference operator()(size_type row, size_type col);
  const_reference operator()(size_type row, size_type col) const;

  vec3d row(size_type row) const;
  vec3d column(size_type col) const;

  //////////////
  // Mutators //
  //////////////
  void clear(value_type value=0.0f);
  void identity(value_type diag=1.0f);

  void set(const vec3d& X, const vec3d& Y, const vec3d& Z);
  void setDiagonal(value_type d);
  void setDiagonal(const vec3d& d);

  void setRow(const vec3d& v, size_type row);
  void setColumn(const vec3d& v, size_type col);

  mat3d transpose(void) const;

  ///////////////
  // Operators //
  ///////////////
  mat3d operator=(const mat3d& m);

  mat3d operator+(const mat3d& m) const;
  mat3d operator-(const mat3d& m) const;
  mat3d operator*(const mat3d& m) const;
  vec3d operator*(const vec3d& v) const;
  mat3d operator*(value_type scale) const;
  mat3d operator/(value_type scale) const;

  mat3d& operator+=(const mat3d& m);
  mat3d& operator-=(const mat3d& m);
  mat3d& operator*=(const mat3d& m);
  mat3d& operator*=(value_type scale);
  mat3d& operator/=(value_type scale);
  
  /////////////
  // Friends //
  /////////////
  friend void swap(mat3d& a, mat3d& b) { a._swap(b); }

  friend vec3d operator*(const vec3d& v, const mat3d& m)   { return m._premultiply(v); }
  friend mat3d operator*(value_type scale, const mat3d& m) { return (m * scale); }

  friend void transpose(mat3d& m) { m._transpose(); }

  friend std::ostream& operator<<(std::ostream& s, const mat3d& m)
  {
    s << "[[" << m(0,0) << ", " << m(0,1) << ", " << m(0,2) << "],[";
    s         << m(1,0) << ", " << m(1,1) << ", " << m(1,2) << "],[";
    s         << m(2,0) << ", " << m(2,1) << ", " << m(2,2) << "]]";
    return s;
  }
  
 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(mat3d& m);
  void _assign(const mat3d& m);

  void _transpose(void);

  reference _at(size_type row, size_type col);
  const_reference _at(size_type row, size_type col) const;

  vec3d _premultiply(const vec3d& v) const;

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  value_type _data[9];
};

#endif /* _MAT3D_H_ */

