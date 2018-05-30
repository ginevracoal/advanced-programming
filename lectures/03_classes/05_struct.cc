#include <iostream>

// by default struct members have public access
struct Point_s {
  double x;
  double y;
};

class Point_c {
  double x;
  double y;
};

int main() {
  Point_s ps;

  // dot operator is used to access private members of a class by value
  ps.x = 9.9;
  ps.y = 3. / 7;

  Point_c pc;
  // pc.x =7.6; // error

  Point_s* p = &ps;

  // arrow operator is used to access the member of a class by reference
  p->x = 0.0;

  std::cout << p->y << std::endl;

  return 0;
}
