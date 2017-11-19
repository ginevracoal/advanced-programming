#include <iostream>
#include <string>
//Write a function that reads from stdin until a valid number is fed
//Change the behavior of the getters function implemented in session 01 such that they throw an exception if an invalid argument is passed. Remember to properly catch the exception.

using namespace std;

struct Not_a_number {};
void get_number();

int main(){
	double number;	
	try {
		cout << "Enter a number\n"; 
		while(cin >> number){
		}
		get_number();
		cout << "This is a number\n";
		return 0;
	} catch (const Not_a_number){
		cerr << "This is not a number.\n";
		return 1;
	} catch (...){
		cerr << "Unknown exception. Aborting.\n";
		return 2;
	}
	cout << "Enter a number\n"; 
	
}

void get_number(){
 if (!cin)
		cin.clear(); // clear error flags
    cin.ignore(100, '\n'); // ignores remainder of stream
		throw Not_a_number{};
}
