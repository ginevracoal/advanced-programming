#include <ap_error.h>
#include <iostream>

struct Animal {
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    if (weight < 0) AP_error("invalid weight:", w);
  }

  Animal() : Animal{0, 0} {}  // delegating constructor

  virtual void speak() const noexcept { std::cout << "Unknown\n"; }
  virtual void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }

  virtual ~Animal() {}
};

struct Dog : public Animal {
  void speak() const noexcept override { std::cout << "Bau\n"; }
  // The function speak() is virtual. You write override to indicate that.

  // If I write
  // void speak() const noexcept override final { std::cout << "Bau\n"; }
  // it means that speak overrides but cannot be overrited.

  Dog() = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}
};

struct Snake : public Animal {
  bool dangerous;
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {}
  Snake(const bool b) : Animal{}, dangerous{b} {}
  void info() const noexcept override {
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept override { std::cout << "ssss\n"; }
};

inline void newline() noexcept { std::cout << std::endl; }

void print_animal(const Animal& a) noexcept {
  std::cout << "throught ref\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Snake s{true};
    s.info();
    s.speak();

    newline();

    // There exists an hidden id associated to Snake,
    // which is used to access the virtual table in the right place
    Animal* p = new Snake{1, 2.3, false};

    std::cout << "through pointer\n";
    p->info();
    p->speak();  // Now it calls the speak function of Snake,
                 // but the call to an override is slower.

    delete p;

    newline();

    print_animal(s);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
