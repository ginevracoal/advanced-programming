/* EXERCISE SESSION 03

Helper functions

Implement the following external helper functions (i.e., they are not part of
the class):

    bool operator==(const Date& lhs, const Date& rhs);
    bool operator!=(const Date& lhs, const Date& rhs);
    std::ostream& operator<<(std::ostream& os, const Date& d);
    optional bool is_leap(const int y);

*/

#include <iostream>
#include <string>
using namespace std;

// scoped enum
enum class M { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

class Date {
  // these members are private by default
  int _day;
  int _month;
  int _year;

 public:
  // constructor declaration and definition
  Date(int d, int m, int y) : _day{d}, _month{m}, _year{y} {}

  // inlined member functions

  // returns the number of days in a month
  int days_in_month(int month, int year);

  // adds n days to date
  void add_days(const unsigned int n, Date date);

  int day() const { return _day; }
  int month() const { return _month; }
  int year() const { return _year; }

  void setDate(int d, int m, int y) {
    _day = d;
    _month = m;
    _year = y;
  }

  // destructor
  ~Date() {}
};

// test for leap years
bool is_leap(int year) {
  return ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0));
}

int Date::days_in_month(int month, int year) {
  switch (M(month)) {
    case M::jan:
    case M::mar:
    case M::may:
    case M::jul:
    case M::aug:
    case M::oct:
    case M::dec:
      return 31;

    case M::apr:
    case M::jun:
    case M::sep:
    case M::nov:
      return 30;

    case M::feb:
      if (is_leap(year) == true) {
        return 29;
      } else {
        return 28;
      }
  }
}

void Date::add_days(const unsigned int n, Date date) {
  int day = date.day();
  int month = date.month();
  int year = date.year();

  for (int i = 0; i < n; ++i) {
    if (day == days_in_month(month, year)) {
      day = 1;
      if (month == int(M::dec)) {
        month = int(M::jan);
        ++year;
      } else
        month = int(month) + 1;
    } else {
      ++day;
    }
  }

  setDate(day, month, year);
}

// helper functions

bool operator==(const Date& lhs, const Date& rhs) {
  return ((lhs.day() == rhs.day()) && (lhs.month() == rhs.month()) &&
          (lhs.year() == rhs.year()));
}

bool operator!=(const Date& lhs, const Date& rhs) { return !(lhs == rhs); }

std::ostream& operator<<(std::ostream& os, const Date& d) {
  return os << d.day() << "/" << d.month() << "/" << d.year();
}

int main() {
  int day, month, year, n_days;

  cout << "Insert the date (dd/mm/yyyy).\n";
  cin >> day;
  if (cin.get() != '/') {
    std::cout << "expected /\n";
    return 1;
  }
  std::cin >> month;
  if (std::cin.get() != '/') {
    std::cout << "expected /\n";
    return 1;
  }
  std::cin >> year;

  Date date(day, month, year);  // create a Date object called date
  Date new_date(day, month, year);

  cout << "Insert the number of days.\n";
  cin >> n_days;

  new_date.add_days(n_days, new_date);

  // using helper functions
  if (new_date == date) {
    cout << "The dates are equal.\n";
  } else if (new_date != date) {
    cout << "The dates are different.\n";
    cout << "The new date is: " << new_date << endl;
  }

  return 0;
}
