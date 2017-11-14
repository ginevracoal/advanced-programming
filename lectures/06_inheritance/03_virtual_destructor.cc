#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  ~Base() { std::cout << "~Base\n"; }
  // If you have  avirtual function
  // make sure to put this destructor as virtual:
  // virtual ~Base() { std::cout << "~Base\n"; }
};

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
  { Derived d; }  // Derived is called and
                  // immediately destroyed.

  std::cout << "\n\npointers\n";
  Base* p = new Derived;  // I create an object Derived
                          // and assign it to a pointer to Base.
                          // This does not destroy Derived.
  delete p;

  return 0;
}
