#include <iostream>
#include <memory>
#include "../04_error_handling/ap_error.h"

template <typename num>
class Vector {
  std::size_t _size;
  // std::size_t is the unsigned integer type of the result of the sizeof
  // operator.

  std::unique_ptr<num[]> elem;
  // std::unique_ptr is a smart pointer that owns and manages another object
  // through a pointer and disposes of that object it goes out of scope
  // In this case elem manages the dynamically-allocated array num[]

 public:
  // custom ctor
  explicit Vector(const std::size_t length)
      // explicit specifies that the constructor doesn't allow implicit
      // conversions of the argument.
      : _size{length},
        elem{new num[length]{}} {
    std::cout << "custom ctor\n";
  }

  // Vector(const std::initializer_list<num> args)
  //     : _size{args.size()}, elem{new num[_size]} {
  //   std::cout << "list ctor\n";
  //   std::uninitialized_copy(args.begin(), args.end(), begin());
  // }

  // default ctor
  Vector() { std::cout << "default ctor\n"; }
  // Vector() = default;
  // Vector() : _size{}, elem{} { std::cout << "default ctor\n"; }

  // copy semantics
  // copy ctor -- deep copy
  Vector(const Vector& v);
  // A copy constructor is a member function which initializes an object using
  // another object of the same class.
  // Default constructor does only shallow copy. Deep copy is possible only
  // with  user defined copy constructor: in this case we make sure that
  // pointers of copied object point to new memory locations.

  // copy assignment -- deep copy
  Vector& operator=(const Vector& v);
  // The copy assignment operator is called when an object appears on the left
  // side of an assignment expression and deals with an already constructed
  // object on the right side of the assigment.
  // It takes as an argument an lvalue reference which is a const, because of
  // course I don't want to modify a copied object.

  // move semantics
  // move ctor
  Vector(Vector&& v) noexcept : _size{std::move(v._size)},
                                elem{std::move(v.elem)} {
    std::cout << "move ctor\n";
  }
  // The move constructor is typically called when an object is initialized from
  // rvalue, in this case being std::move(v1).
  // std::move

  // move assignment
  Vector& operator=(Vector&& v) noexcept {
    std::cout << "move assignment\n";
    _size = std::move(v._size);
    elem = std::move(v.elem);
    return *this;
  }
  // It takes as an argument an rvalue reference.
  // It creates a new object by using as much memory from passed object.
  // noexcept tells the compiler that the operator does not throw exceptions.

  const num& operator[](const std::size_t& i) const noexcept { return elem[i]; }
  num& operator[](const std::size_t& i) noexcept { return elem[i]; }

  std::size_t size() const noexcept { return _size; }

  // range-for
  const num* begin() const noexcept { return &elem[0]; }
  num* begin() noexcept { return &elem[0]; }

  const num* end() const noexcept { return &elem[0] + _size; }
  num* end() noexcept { return &elem[0] + _size; }
};

// copy ctor
template <typename num>
Vector<num>::Vector(const Vector& v) : _size{v._size}, elem{new num[_size]} {
  std::cout << "copy ctor\n";
  for (std::size_t i = 0; i < _size; ++i) elem[i] = v[i];
  // std::uninitialized_copy(v.begin(),v.end(),this->begin()); //use placement
  // new
}

// copy assignment
template <typename num>
Vector<num>& Vector<num>::operator=(const Vector& v) {
  std::cout << "copy assignment\n";

  // we could decide that this operation is allowed if and only if
  // _size == v._size
  //
  // AP_assert(_size == v._size, "Vector lenght mismatch");
  // probably the just mentioned approach is safier..

  _size = v._size;
  elem.reset(new num[_size]);

  // for (std::size_t i = 0; i < _size; ++i)
  //   elem[i] = v[i];

  std::copy(v.begin(), v.end(), this->begin());
  return *this;

  // is this approach consistent with self-assignment vx=vx?
}

template <typename num>
Vector<num> operator+(const Vector<num>& lhs, const Vector<num>& rhs) {
  const auto size = lhs.size();

  AP_assert(size == rhs.size(), "Vector lenght mismatch:", size, "!=",
            rhs.size(), "\nlhs:", lhs, "\nrhs:", rhs);

  Vector<num> res(size);
  for (std::size_t i = 0; i < size; ++i) res[i] = lhs[i] + rhs[i];

  return res;
}

template <typename num>
std::ostream& operator<<(std::ostream& os, const Vector<num>& v) {
  for (const auto& x : v) os << x << " ";
  os << std::endl;
  return os;
}

int main() {
  try {
    std::cout << "\nVector<int> v0; calls\n";
    Vector<int> v0;
    std::cout << v0.size() << "\n";
    std::cout << "\nVector<int> v00{}; calls\n";
    Vector<int> v00{};
    std::cout << v00.size() << "\n";

    std::cout << "\nVector<double> v1{5}; calls\n";
    // Vector v1{5}; // perché funziona lo stesso? devo specificare per forza il
    // type? non ho capito explicit allora...
    Vector<double> v1{5};

    std::cout << "\nVector<double> v2 = v1; calls\n";
    Vector<double> v2 = v1;
    std::cout << "\nv2 = Vector<double>{7}; calls\n";
    v2 = Vector<double>{7};
    // In questo caso chiama il move assignment perché Vector<double>{7} è un
    // rvalue che va assegnato a qualche variabile, ovvero il suo indirizzo è
    // assegnato a v2.

    std::cout << "\nVector<double> v3{std::move(v1)}; calls\n";
    Vector<double> v3{std::move(v1)};  // now v1 should not be used

    std::cout << "\nv3 = v2; calls\n";
    v3 = v2;
    // Chiama il copy assignment perché v2 esiste già e viene copiato nella
    // variabile v3 in un nuovo indirizzo (deep copy)

    std::cout << "\nv2 = " << v2;
    std::cout << "v3 = " << v3;

    std::cout << "\nassign some values to v3\n";
    {
      // auto i = v3.size();
      // while (i--)
      //   v3[i] = i;

      int c = 0;
      for (auto& x : v3) x = c++;
    }
    // v3=v3;
    std::cout << "\nv2 = " << v2;
    std::cout << "v3 = " << v3;

    std::cout << "\nVector<double> v4{v3 + v3}; calls\n";
    Vector<double> v4{v3 + v3};

    std::cout << "v4 = " << v4;

    std::cout << "\nNRVO: Named Return Value Optimization\n";

    std::cout << "\nv4 = v3 + v3 + v2 + v3; calls:\n";
    v4 = v3 + v3 + v2 + v3;
    // Chiama il move assignment perché sto creando la variabile somma e devo
    // assegnare l'indirizzo ad una nuova variabile
    std::cout << "v4 = " << v4;

    std::cout << "\nLet's test our assert in operator+\n";
    std::cout << "Vector<int> a{5};\n"
              << "Vector<int> b{7};\n"
              << "Vector<int> c{a + b}\n";
    Vector<int> a{5};
    Vector<int> b{7};
    Vector<int> c{a + b};
    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
