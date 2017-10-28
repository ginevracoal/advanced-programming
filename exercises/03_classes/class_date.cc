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
enum class M{jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
	
class Date {
	//these members are private by default
  int day, year;
	M month;
	//char month[4];

	//test for leap years
	bool is_leap(int year) const{
		return ((year % 4 ==0) && (year %100 != 0 || year % 400 == 0));
	}
	
	//adds one day
	Date following_day(Date date); 
	
  public:
		//constructor declaration and definition
		Date(int d, int m, int y): day{d}, month{M(m)}, year{y} {}

		//inlined member functions

		//returns the number of days in month
		int month_days(M month);

		//adds n days to date
		Date add_days(int n, Date date){
		for (int i=0; i<n; i++)
			date = following_day(date);
		return date;		
		}
		
    int get_day() const {return day;} 
    M get_month() const {

		return month;
		}

    int get_year() const {return year;}

		void print_date(Date date){
			cout << date.get_day() << endl;
			cout << int(date.get_month()) << endl;
			cout << date.get_year() << endl;
		}

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


Date Date::following_day(Date date){

	int day = date.get_day();
	M month = date.get_month();
	int year = date.get_year();

	if(month_days(month) == 31){
		if (month == M::dec){
				month = M::jan;
				++year;
			}
		day == 1;
		month = M( int(month) + 1 ); //
	} else {
		++day;
	}

		
	
	date.day = day;
	date.month = month;
	date.year = year;

	return date;
}


int main(int argc, char * argv[]){
	cout << "Insert the date and the number of days.\n";

	int day = atoi(argv[0]);
	int month = atoi(argv[1]);
	int year = atoi(argv[2]);

	Date date(day, month, year); //create a Date object called date

	//call public member functions
  date.add_days(atoi(argv[3]), date);
	date.print_date(date);
  
	
	return 0;
}


