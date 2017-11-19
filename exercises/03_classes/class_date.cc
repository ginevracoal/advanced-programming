/* EXERCISE SESSION 03 - class date

Implement a class Date. This class must meet the following requirements:

    it has three private attributes to represent day, month and year
    use a scoped enum for month
    it has the following public functions:
        it has a constructor that takes as arguments a day, a month and a year.
(Forget about the validation for now)
        it has a day() function that returns the day
        it has a month() function that returns the month
        it has a year() function that returns the year
        it has a function add_day(const unsigned int n) which adds n days. You
have to take care to increment months and years accordingly (neglect leap years)
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

  // void setDate(int d, int m, int y) {
  //   _day = d;
  //   _month = m;
  //   _year = y;
  // }

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

  cout << "The new date is: ";
  cout << day << "/" << month << "/" << year << endl;
  // setDate(day, month, year);
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

  cout << "Insert the number of days.\n";

  cin >> n_days;

  date.add_days(n_days, date);

  // date.print_date(date);

  return 0;
}
