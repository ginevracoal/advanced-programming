// std::unique_ptr belongs to header memory
// std::unique_ptr is a smart pointer that owns and manages another object
// through a pointer and disposes of that object when the unique_ptr goes outof
// scope. std::unique_ptr is commonly used to manage the lifetime of objects.
// In this version unique_ptr manages a single object allocated with new.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

// ========== std::unique_ptr ==========
template <typename T>
class unique_ptr {
  T* ptr;

 public:
  // CLASS CONSTRUCTORS
  unique_ptr() : ptr{nullptr} {  // it is a nullptr if no object is owned
#ifdef DEBUG
    cout << " calls default ctor";
#endif
  }

  // Explicit constructor
  unique_ptr(T* p) : ptr{p} {
#ifdef DEBUG
    cout << " calls explicit ctor";
#endif
  }

  // CLASS DESTRUCTOR
  // The owned object is destroyed
  ~unique_ptr() {
    // if (get() != nullptr) ??
    reset();
  }

  // MODIFIERS

  // swaps the managed objects
  // implementare std::swap
  void swap(unique_ptr<T>& u) noexcept { std::swap(ptr, u.ptr); }

  // ===== Move constructor =====
  // Creates a new unique_ptr by transferring the ownership from u to *this
  // Move ctors always take a double reference, also called an rvalue reference.
  // Move operators should be marked as noexcept in order to tell the compiler
  // that they will not throw any exception and allow the optimization of move
  // operations
  unique_ptr(unique_ptr<T>&& u) noexcept {
#ifdef DEBUG
    cout << " calls move ctor";
#endif
    unique_ptr<T> tmp{u.release()};  // release the ownership of the object
    // ptr = std::move(u.ptr);
    // u.ptr = nullptr;
    tmp.swap(*this);  // swap the objects managed by u and current unique_ptr
  }

  // ===== Move assignment =====
  // Transfers the ownership from u to *this

  unique_ptr<T>& operator=(unique_ptr<T>&& u) noexcept {
#ifdef DEBUG
    cout << " calls move assignment";
#endif
    // unique_ptr<T> tmp{u.release()};  // why?
    // if (this != &tmp) {
    //   tmp.swap(*thkis);
    // }

    if (this != &u)  // if they have a different address
      reset(u.release());
    return *this;  // memory address of the unique_ptr
  }

  // ===== Remove copy semantics =====
  // unique_ptr has no copy constructor!

  // perché in questi case unique ptr non è templated?
  // Copy constructor
  unique_ptr(unique_ptr const&) = delete;
  // Copy assignment
  unique_ptr& operator=(unique_ptr const&) = delete;

  // Releases the ownership of the managed object and returns a pointer to it
  // (so it does not destroy the object)
  T* release() noexcept {
    T* tmp = get();
    ptr = nullptr;  // prt releases the managed object
    return tmp;
  }

  // Destroys the object currently managed by the unique_ptr (if any) and takes
  // the ownership of new_ptr
  void reset(T* new_ptr = nullptr) {
    if (new_ptr != get()) {  // if the new object is different
      T* tmp = release();    // release currently owned object
      ptr = new_ptr;         // take the ownership of new_ptr
      delete tmp;
    }
  }

  // OBSERVERS

  // Returns a pointer to the managed object
  T* get() const { return ptr; }

  // Checks if *this owns something or not. This is a conversion
  // operator, which allows to use *this as bool.
  operator bool() { return ptr != nullptr; }  // va bene anche return ptr?

  // DEREFERENCE OPERATORS

  // Returns the object owned (pointed to) by *this
  T& operator*() { return *ptr; }
  // Returns a pointer to the object onwed by *this
  T* operator->() { return get(); }  // or return ptr;

  // EXTRA FUNCTION

  // I wrote this just to understand how everything works.
  void understand(const char name) {
    cout << endl;
    // ptr has access to its own memory address through this pointer.
    // so *this is the object of the pointer this, which is simply ptr.
    // cout << "\nthis: " << this;
    cout << "\n&" << name << ": " << &ptr;
    // ptr == get()
    cout << "\n" << name << ": " << ptr;
    // cout << "\nget(): " << get();
    // ptr == **this
    cout << "\n*" << name << ": " << *ptr;
    // cout << "\n**this: " << **this;

    // so what is *this? it is the unique_ptr itself!!
    // cout << "\n*this: " << *this;
    // this is not an object! it is just a reference

    cout << endl;
  }
};

// Non-member functions

int main() {
  cout << "\nu{}";
  unique_ptr<int> u{};  // default ctor

  int* ptr = new int;
  *ptr = 6;

  cout << "\np{ptr}";
  unique_ptr<int> p{ptr};  // explicit ctor
  p.understand('p');

  // u = ptr; // copy is not permitted!

  cout << "\nu = move(ptr)";
  u = move(p);  // move assignment
  u.understand('u');

  cout << "\nw{move(u)}";
  unique_ptr<int> w{move(u)};  // move ctor
  w.understand('w');

  return 0;
}
