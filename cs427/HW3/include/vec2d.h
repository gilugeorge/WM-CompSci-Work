#ifndef _VEC2D_H_
#define _VEC2D_H_

#include <ostream>
#include <cmath>

class vec2d {
 public:
  //////////////////
  // Data Members //
  //////////////////
  union {
    struct { float x, y; };
    struct { float u, v; };
    float data[2];
  };

 public:
  /////////////////
  // Constructor //
  /////////////////
  explicit vec2d(float value=0.0f);
  vec2d(float x, float y);
  vec2d(const vec2d& v);
 
  /////////////////
  // Desctructor //
  /////////////////
  ~vec2d(void) {}

  ////////////////
  // Inspectors //
  ////////////////
  size_t size(void) const { return 2; }

  float  operator[](size_t index) const;
  float& operator[](size_t index);

  ///////////////
  // Operators //
  ///////////////
  vec2d& operator=(const vec2d& v);

  bool operator==(const vec2d& v) const;
  bool operator!=(const vec2d& v) const;
  
  vec2d operator+(const vec2d& v) const;
  vec2d operator-(const vec2d& v) const;
  vec2d operator*(const vec2d& v) const;
  vec2d operator*(float scale) const;
  vec2d operator/(const vec2d& v) const;
  vec2d operator/(float scale) const;

  vec2d& operator+=(const vec2d& v);
  vec2d& operator-=(const vec2d& v);
  vec2d& operator*=(const vec2d& v);
  vec2d& operator*=(float scale);
  vec2d& operator/=(const vec2d& v);
  vec2d& operator/=(float scale);

  ///////////////
  // Modifiers //
  ///////////////
  float dot(const vec2d& v) const;
  float squared_length(void) const;
  float length(void) const;
  float squared_distance(const vec2d& v) const;
  float distance(const vec2d& v) const;

  vec2d normalize(void) const;

  /////////////
  // Friends //
  /////////////
  friend void  swap(vec2d& a, vec2d& b)                { return a._swap(b); }
  friend void  normalize(vec2d& v)                     { v /= v.length(); }
  friend vec2d operator*(float scale, const vec2d& v)  { return (v*scale); }

  friend std::ostream& operator<<(std::ostream& s, const vec2d& v)
  {
    s << "[" << v.x << "," << v.y << "]";
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _assign(const vec2d& v);
  void _swap(vec2d& v);
};

#endif /* _VEC2D_H_ */
