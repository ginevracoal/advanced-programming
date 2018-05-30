#include <iostream>
#include <string>

// tells the compiler that this class uses a generic value num
template <typename num>
class Vector {
  num* elem;
  unsigned int _size;

 public:
  Vector(const unsigned int size) : _size{size}, elem{new num[size]} {}

  ~Vector() { delete[] elem; }

  unsigned int size() const { return _size; }

  num& operator[](const unsigned int i) { return elem[i]; }

  const num& operator[](const unsigned int i) const { return elem[i]; }

  void pretty_print() const;
};

int main() {
  Vector<double> v{10};

  // For variables, auto specifies that the type of the variable that is being
  // declared will be automatically deduced from its initializer
  for (auto i = 0; i < v.size(); ++i) v[i] = i;

  v.pretty_print();

  Vector<double>* pv = &v;

  pv->pretty_print();

  return 0;
}

// The member functions must all be treated as generic functions. I have
// to add the template command to each member function.
template <typename num>
void Vector<num>::pretty_print() const {
  std::cout << "Vector allocated at " << elem << std::endl;
  for (auto i = 0; i < _size; ++i)
    std::cout << "elem[" << i << "] = " << elem[i] << std::endl;
}
