#ifndef UNIQUE_PTR
#define UNIQUE_PTR

/**
* std::unique_ptr is a smart pointer that owns and manages another object
* through a pointer and disposes of that object when the unique_ptr goes out of
* scope. std::unique_ptr is commonly used to manage the lifetime of objects.
* In this version unique_ptr manages a single object alllocated with new.
*/

// T is the type of the object managed by the unique_ptr
template <typename T>
class unique_ptr {
  T* ptr;

 public:
  // MEMBER FUNCTIONS

  // class constructors
  unique_ptr() : ptr{0} {}
  unique_ptr(T* p) : ptr{p} {}

  // move constructor
  unique_ptr(unique_ptr&& p) : ptr{p.release()} {}

  // class destructor
  /** simply resets the the ownership of the object, so that ptr = nullptr
   * (points to nothing)*/
  ~unique_ptr() { reset(); }

  /** move assignment assigns the unique_ptr to an object (transfers the
   * ownership from u to *this) */
  /** Only non-const unique_ptr can transfer the ownership of the managed object
   * to another unique_ptr. If an object's lifetime is managed by a const
   * std::unique_ptr, it is limited to the scope in which the pointer was
   * created.
   */
  unique_ptr& operator=(unique_ptr&& u) noexcept {
    reset(u.release());  // perchè?
    return *this;
  }

  // unique_ptr& operator=() noexcept {
  //   reset();  // perchè?
  //   return *this;
  // }

  // MODIFIERS

  /** release releases the ownership of the object and returns a pointer to it
   */
  T* release() {
    T* p = get();   // pointer to the managed object
    ptr = nullptr;  // ptr releases the object
    return p;
  }

  /** reset replaces the managed object with another one */
  void reset(T* new_ptr = nullptr) {
    // this way, if I call reset() the default parameter is nullptr.
    if (new_ptr != get()) {  // if the new pointer has a different address
      ptr = new_ptr;
    }
  }

  // OBSERVERS

  /** get returns a pointer to the managed object */
  T* get() const { return ptr; }

  /** operator-> dereferences the unique_ptr*/
  T* operator->() const { return get(); }

  /** operator bool checks whether the unique_ptr owns something or not*/
  operator bool() const { return this != nullptr; }
};

// NON MEMBER FUNCTIONS

template <typename T, typename U>
bool operator==(const unique_ptr<T>& x, const unique_ptr<U>& y) noexcept {
  return x.get() == y.get();
}

template <typename T>
bool operator==(const unique_ptr<T>& x, std::nullptr_t) noexcept {
  return x.get() == nullptr;
}

template <typename T, typename U>
bool operator!=(const unique_ptr<T>& x, const unique_ptr<U>& y) noexcept {
  return x.get() == y.get();
}

template <typename T>
bool operator!=(const unique_ptr<T>& x, std::nullptr_t) noexcept {
  return x.get() == nullptr;
}

#endif