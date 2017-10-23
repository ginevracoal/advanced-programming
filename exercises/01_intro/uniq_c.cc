#include <iostream>
#include <string>

//Modify the above program to reproduce the behavior of uniq -c.

using namespace std;

int main() {
  string line;
  string newline;
  int x=1; //contatore per il numero di occorrenze di una stringa
  getline(cin,line); //leggo la prima stringa
  while(getline(cin,newline)){//leggo la stringa successiva
  	//se la nuova stringa è diversa, stampo l'ultima insieme al suo numero di occorrenze
  	if (newline != line){
       cout << x << " " << line << endl; 
       line = newline;
       x=1;
    //se la nuova stringa è uguale a quella di prima incremento il contatore delle occorrenze
  	} else {
  	   x+=1;
  	}
  }
  cout << x << " " << line << endl; 
  return 0;
}  


