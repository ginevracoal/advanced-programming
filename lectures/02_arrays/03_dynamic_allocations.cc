#include <iostream>

int main() {
  std::cout << "Please insert array lenght: ";
  int n;
  std::cin >> n;
  // the operator new allocates a block of memory on the heap for an array and
  // returns a pointer to the first element of this block
  int* da = new int[n];  // allocated on the HEAP, or free-store

  for (int i = 0; i < n; ++i) da[i] = i * 10;

  for (int i = 0; i < n; ++i)
    std::cout << "da[" << i << "] = " << da[i] << std::endl;

  // the operator delete frees the block of memory previously allocated and
  // takes as an argument a pointer to this block
  delete[] da;
  return 0;
}
