/* EXERCISE SESSION 03 - class date

Implement a class Date. This class must meet the following requirements:

    it has three private attributes to represent day, month and year
    use a scoped enum for month
    it has the following public functions:
        it has a constructor that takes as arguments a day, a month and a year. (Forget about the validation for now)
        it has a day() function that returns the day
        it has a month() function that returns the month
        it has a year() function that returns the year
        it has a function add_day(const unsigned int n) which adds n days. You have to take care to increment months and years accordingly (neglect leap years)
*/

#include <iostream>
using namespace std;

//scoped enum
enum class M{jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
	
class Date {
	//these members are private by default
  int day, year;
	M month;

	//test for leap years
	bool is_leap(int year) const{
		return ((year % 4 ==0) && (year %100 != 0 || year % 400 == 0));
	}
	
	//adds one day
	Date following_day(); 
	
  public:
		//constructor declaration
		Date(int day, M month, int year);
		
		//inlined member functions
    int get_day() const {return day;} 
    M get_month() const {return month;}
    int get_year() const {return year;}

		void set_day(int d){d = day;}
		void set_month(M m){m = month;}
		void set_year(int y){y = year;}

		Date add_days(const unsigned int n, Date date){
		int i;
		for (i=0; i<n; i++)
			following_day(date);
		return date;
		}

		int month_days(M month);
		void print_date(Date date);

		//destructor
		~ Date(){}
};

int Date::month_days(M month){
	switch (month){
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
		  return 28;
	}
} 


//parametrized constructor definition
Date::Date(int d, M m, int y): day{d}, month{m}, year{y} {}

void Date::print_date(Date date){
		cout << day << " " << month << " " << year << endl;
}

//inserire il dettaglio dell'anno bisestile!!
Date Date::following_day(Date date){
	if(day > month_days(get_month(date))){
		get_day(date)=1;
		++get_month(date);
	} else {
		++get_day(date);
	}

	if (get_month(date)>12){
		get_month(date)=1;
		++get_year(date);
	}	

	return date;
}



int main(int argc, char *argv[]){
	cout << "Insert the date and the number of days.\n";
	
	Date date;

	date.set_day(atoi(argv[0]));
	date.set_month(argv[1]);
  date.set_year(atoi(argv[2]));

  date.add_days(argv[3], date); //call member function
	date.print_date(date);
	return 0;
}





