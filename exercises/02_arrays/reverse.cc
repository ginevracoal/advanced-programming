/* THIS VERSION IS ONLY FOR INT TYPE

Write a program that reads from stdin the length of an array and then store in it the numbers given from stdin. The program should then print the numbers in reverse order. Remember to properly free the used memory. You should divide the problem in two parts:

Write one template function that allocates on the heap one array of a given size, initializes its elements and returns the pointer to the first element.

Write a template function that prints the elements of an array in the reverse order.

Test with integers and doubles.*/

#include <iostream>
#include <string>

using namespace std;

//allocates on the heap an array of a given size, initializes its elements and returns the pointer to the first element

int* allocate(int n){
  int* array = new int [n]; //allocates on the HEAP an array of size lenght and defines a pointer to its first element array[0]
  for(int i=0; i<n; i++)
    cin >> array[i];
  return array;
  delete[] array;
}

//prints the elements of an array in the reverse order
void print(int n, int* array){
  for (int i=n-1; i>=0; i--){
    cout << array[i] << " ";
  }
  cout << endl;
}


int main(){
  int lenght;
  cout << "Enter the lenght of the array\n";
  cin >> lenght;
  print(lenght, allocate(lenght));
  return 0;
}

