#ifndef _OBJ_DETAIL_H_
#define _OBJ_DETAIL_H_

///////////////////////////////////////////
// Helper Class for storing polygon data //
///////////////////////////////////////////
namespace detail {

class polygon {
 public:
  /////////////////
  // Constructor //
  /////////////////
  polygon(void) {}
  polygon(const polygon& p)
  {
    _vertexIndex = p._vertexIndex;
    _normalIndex = p._normalIndex;
    _textureIndex = p._textureIndex;
  }

  ///////////////
  // Operators //
  ///////////////
  polygon operator=(const polygon& p)
  {
    _assign(p);
    return *this;
  }

  /////////////
  // Methods //
  /////////////
  void addV(unsigned int vertex)
  {
    _vertexIndex.push_back(vertex);
    _normalIndex.clear();
    _textureIndex.clear();
  }


  void addVN(unsigned int vertex, unsigned int normal)
  {
    _vertexIndex.push_back(vertex);
    _normalIndex.push_back(normal);
    _textureIndex.clear();
  }


  void addVT(unsigned int vertex, unsigned int textureCoord)
  {
    _vertexIndex.push_back(vertex);
    _normalIndex.clear();
    _textureIndex.push_back(textureCoord);
  }


  void addVNT(unsigned int vertex, unsigned int normal, unsigned int textureCoord)
  {
    _vertexIndex.push_back(vertex);
    _normalIndex.push_back(normal);
    _textureIndex.push_back(textureCoord);
  }


  unsigned int size(void) const
  {
    return _vertexIndex.size();
  }


  bool hasNormals(void) const
  {
    return !_normalIndex.empty();
  }


  bool hasTextureCoordinates(void) const
  {
    return !_textureIndex.empty();
  }


  unsigned int vertexIndex(unsigned int vertex) const
  {
    assert(vertex < _vertexIndex.size());
    return _vertexIndex[vertex];
  }


  unsigned int normalIndex(unsigned int vertex) const
  {
    assert(vertex < _normalIndex.size());
    return _normalIndex[vertex];
  }


  unsigned int textureCoordIndex(unsigned int vertex) const
  {
    assert(vertex < _textureIndex.size());
    return _textureIndex[vertex];
  }


  /////////////
  // Friends //
  /////////////
  friend void swap(polygon& a, polygon& b) { a._swap(b); }


 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _assign(const polygon& p)
  {
    if(&p == this) return;
    
    // copy
    polygon temp(p);
    _swap(temp);

    // Done.
  }


  void _swap(polygon& p)
  {
    std::swap(_vertexIndex, p._vertexIndex);
    std::swap(_normalIndex, p._normalIndex);
    std::swap(_textureIndex, p._textureIndex);
  }


  //////////////////////////
  // Private Data Members //
  //////////////////////////
  std::vector<unsigned int> _vertexIndex;
  std::vector<unsigned int> _normalIndex;
  std::vector<unsigned int> _textureIndex;
};

} // namspace detail end


#endif /* OBJ_DETAIL_H_ */
