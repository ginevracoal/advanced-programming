#include <iostream>
#include <string>

//Write a simple version of the Unix program uniq, which, when fed with a text, outputs the same text with adjacent identical lines collapsed to one.

using namespace std;

int main() {
  string line;
  string oldline;
  
  while(getline(cin,line)){
  	if (line != oldline){
  		cout << line << endl;
  	}
  	oldline = line;
  }
  return 0;
}  



