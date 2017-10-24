/* Write a program that reads from stdin the length of an array and then store in it the numbers given from stdin. The program should then print the numbers in reverse order. Remember to properly free the used memory. You should divide the problem in two parts:

Write one template function that allocates on the heap one array of a given size, initializes its elements and returns the pointer to the first element.

Write a template function that prints the elements of an array in the reverse order.

Test with integers and doubles.*/


#include <iostream>
#include <string>

using namespace std;

//allocates on the heap an array of a given size, initializes its elements and returns the pointer to the first element
template <typename T>
T* allocate(int n){
  T* array = new T [n]; //allocates on the HEAP an array of size n and defines a pointer to its first element array[0]
  for(int i=0; i<n; i++)
    cin >> array[i];
  return array;
  delete[] array; //deallocates the memory block previously occupied using new[]
}

//prints the elements of an array in the reverse order
template <typename T>
void print_rev(int n, T* array){
  for (int i=n-1; i>=0; i--){
    cout << array[i] << " ";
  }
  cout << endl;
}


int main(){
  int lenght;
  
  cout << "Enter the lenght of the array\n";
  cin >> length;
  
  print_rev(length, allocate(length));
  return 0;
}

