#include <iostream>
#include <string>
//Write a function that reads from stdin until a valid number is fed
//Change the behavior of the getters function implemented in session 01 such that they throw an exception if an invalid argument is passed. Remember to properly catch the exception.

using namespace std;

struct Not_a_number {};

int main(){
	try {
		double x;
		while(cin >> x){
			cout << "Enter a number\n"; 
			get_number(x);
		}
		return 0;
	} catch (void Not_a_number){
		cerr << "This is not a number.\n";
		return 1;
	}

//  }
//  if(!cin){
//      cin.clear(); // clear error flags
//      cin.ignore(100, '\n'); // ignores remainder of stream
//      cout << "This is not a number\n";
//  }
}


void get_number(double x){
 if (!cin)
}
