/* EXERCISE SESSION 04

Date

Improve the class Date that you developed in the previous exercise session such
that it throws an exception whenever an invalid date is provided.

*/

#include <iostream>
#include <string>

using namespace std;

enum class M { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

struct missing_symbol {};
struct invalid_day {};
struct invalid_month {
  string message;
};
struct invalid_year {
  string message;
};

// test for leap years
bool is_leap(int year) {
  return ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0));
}

class Date {
  int _day;
  int _month;
  int _year;

 public:
  Date(int d, int m, int y) : _day{d}, _month{m}, _year{y} {
    if (_day > 31 || _day == 0) {
      throw invalid_day{};
    }
    if (_month > 12 || _month == 0) {
      throw invalid_month{" Please enter a number between 1 and 31."};
    } else if (_day > 29 && _month == int(M::feb)) {
      throw invalid_month{" Please choose a month different from february."};
    }
    if (is_leap(_year) == false && _day > 28) {
      throw invalid_year{" Please enter a leap year."};
    }
  }

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

  ~Date() {}
};

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

bool operator==(const Date& lhs, const Date& rhs) {
  return ((lhs.day() == rhs.day()) && (lhs.month() == rhs.month()) &&
          (lhs.year() == rhs.year()));
}

bool operator!=(const Date& lhs, const Date& rhs) { return !(lhs == rhs); }

std::ostream& operator<<(std::ostream& os, const Date& d) {
  return os << d.day() << "/" << d.month() << "/" << d.year();
}

int main() {
  try {
    int day, month, year, n_days;

    cout << "Insert the date (dd/mm/yyyy).\n";

    cin >> day;

    if (cin.get() != '/') {
      throw missing_symbol{};
    }

    cin >> month;

    if (cin.get() != '/') {
      throw missing_symbol{};
    }

    cin >> year;

    Date date(day, month, year);
    Date new_date(day, month, year);

    cout << "Insert the number of days.\n";
    cin >> n_days;

    new_date.add_days(n_days, new_date);

    if (new_date == date) {
      cout << "The dates are equal.\n";
    } else if (new_date != date) {
      cout << "The dates are different.\n";
      cout << "The new date is: " << new_date << endl;
    }
    return 0;
  } catch (const missing_symbol) {
    cerr << "Symbol / is missing.\n";
    return 1;
  } catch (const invalid_day) {
    cerr << "Day value is not valid. Please enter a number between 1 and 31.\n";
    return 2;
  } catch (const invalid_month& s) {
    cerr << "Month value is not valid." << s.message << endl;
    ;
    return 3;
  } catch (const invalid_year& s) {
    cerr << "Year value is not valid." << s.message << endl;
  }
}
