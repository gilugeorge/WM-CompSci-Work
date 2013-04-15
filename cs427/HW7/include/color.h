#ifndef _COLOR_H_
#define _COLOR_H_

#include <ostream>


class color {
 public:
   //////////////////
  // Data Members //
  //////////////////
  union {
    struct { float r, g, b; };
    struct { float red, green, blue; };
    float data[3];
  };

 public:
  /////////////////
  // Constructor //
  /////////////////
  explicit color(float value=0.0f);
  color(float r, float g, float b);
  color(const color& col);
 
  /////////////////
  // Desctructor //
  /////////////////
  ~color(void) {}

  ////////////////
  // Inspectors //
  ////////////////
  const float& operator[](size_t index) const;
  float& operator[](size_t index);

  ///////////////
  // Operators //
  ///////////////
  color& operator=(const color& col);

  bool operator==(const color& col) const;
  bool operator!=(const color& col) const;
  
  color operator+(const color& col) const;
  color operator-(const color& col) const;
  color operator*(const color& col) const;
  color operator*(float scale) const;
  color operator/(const color& col) const;
  color operator/(float scale) const;

  color& operator+=(const color& col);
  color& operator-=(const color& col);
  color& operator*=(const color& col);
  color& operator*=(float scale);
  color& operator/=(const color& col);
  color& operator/=(float scale);

  ///////////////
  // Modifiers //
  ///////////////
  void abs(void);
  void clamp(float lowerBound=0.0f, float upperBounds=1.0f);
  float average(void) const;

  /////////////
  // Friends //
  /////////////
  friend void  swap(color& a, color& b)            { return a._swap(b); }
  friend color operator*(float scale, color& col)  { return (col*scale); }

  friend std::ostream& operator<<(std::ostream& s, const color& col)
  {
    s << "(" << col.r << "," << col.g << "," << col.b << ")";
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _assign(const color& col);
  void _swap(color& col);
};

#endif /* _COLOR_H_ */
