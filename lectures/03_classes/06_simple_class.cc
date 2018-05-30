#include <iostream>
#include <string>

// a class is concrete representation of an object
// a class can collect members of different types
class Vector {
  // by default class members are private, so there's no need to specify this if
  // I write them before the public part

  double* elem;
  unsigned int _size;

 public:
  // class constructor defines the default initialization of the class
  Vector(const unsigned int size) : _size{size}, elem{new double[size]} {}

  // class destructor contains tasks to be completed before going out of scope
  // it releases memory that was allocated by the class constructor and member
  // functions
  ~Vector() { delete[] elem; }

  unsigned int size() const { return _size; }

  double& operator[](const unsigned int i) { return elem[i]; }

  const double& operator[](const unsigned int i) const { return elem[i]; }

  void pretty_print() const;
};

int main() {
  Vector v{10};

  for (auto i = 0; i < v.size(); ++i) v[i] = i;

  v.pretty_print();

  Vector* pv = &v;

  pv->pretty_print();

  return 0;
}

// In a class function definition I have to specify the namespace of that class
void Vector::pretty_print() const {
  std::cout << "Vector allocated at " << elem << std::endl;
  for (auto i = 0; i < _size; ++i)
    std::cout << "elem[" << i << "] = " << elem[i] << std::endl;
}
