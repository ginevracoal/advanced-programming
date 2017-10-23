//Write a simple text formatter that breaks the lines longer than a given number of characters. This formatter does not break words

#include <iostream>
#include <string>

using namespace std;

int main (){

  int N; //maximum number of characters
	int chars = 0; //counter for the number of characters in the current line
  string word;
	unsigned int l;

	cout << "Enter the maximum number of characters.\n";
	cin >> N;
 
	cout << "Now enter the text you want to format.\n";	

  while(cin >> word){

		l = word.length();

		chars += l;

		if (chars <= N){
			cout << word << " ";
		} else {
			cout << "\n" << word;
			chars == 0; 
		}
	}
  return 0;
}

