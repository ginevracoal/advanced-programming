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


class Date {

	//these members are private by default
  int day, year;

	//scoped enum
	enum M{jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
	M month;	

	//test for leap years
	bool is_leap(int year) const{
		return ((year % 4 ==0) && (year %100 != 0 || year % 400 == 0));
	}

	Date following_day(); //adds a single day to date
	int month_days(M month);
	void print_date(Date date);


  public:
		//constructor declaration
		Date(int day, M month, int year);
		
		//inlined member functions
    int get_day() const {return day;} 
    M get_month() const {return month;}
    int get_year() const {return year;}

    Date add_days(const unsigned int n, Date date);
		
		//destructor
		~ Date(){}
};

int month_days(M month){
	switch (month){
		case month::jan:
		case month::mar:
		case month::may:
		case month::jul:
		case month::aug:
		case month::oct:
		case month::dec:
		  return 31;

		case month::apr:
		case month::jun:
		case month::sep:
		case month::nov:
		  return 30;

		case month::feb:
		  return 28;
	}
} 


//parametrized constructor definition
Date::Date(int d, M m, int y): day{d}, month{m}, year{y} {}

void print_date(Date date){
		cout << day << " " << month << " " << year << endl;
	}

//inserire il dettaglio dell'anno bisestile!!
Date following_day(Date date){
	if(day > month_days(month)){
		day=1;
		++month;
	} else {
		++day;
	}

	if (month>12){
		month=1;
		++year;
	}	

	return date;
}


Date Date::add_days(const unsigned int n, Date date){
	int i;
	for (i=0; i<n; i++)
		following_day(date);
	return date;
}


int main(int argc, char *argv[]){
	cout << "Insert the date and the number of days.\n";
	
	Date.get_day(argv[0]);
	Date.get_month(argv[1]);
  Date.get_year(argv[2]);

  Date.add_days(argv[3], date); //call member function
	Date.print_date(date);
	return 0;
}





