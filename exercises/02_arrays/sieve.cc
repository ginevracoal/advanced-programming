/*
Implement the Sieve of Eratosthenes algorithm. Write a code that prints on screen the first prime numbers up to N (included), where N is passed from command line argument. The first prime number that should be printed is 2 
*/

#include <iostream>
#include <math.h>


void sieve(int n, bool A[]){
	int i,j;

//	bool* A= new bool[n-2];

	for (i=2; i<=sqrt(n); i++){
		A[i-2] = true;
		for (j=i*i; j<=n; j+=i)
     	A[j-2] = false;
	}

//	delete[] A;
}

//prints the first n primes
void print_primes(int n, bool A[]){
	std::cout << "The first prime numbers up to " << n << " are: ";	
	
	
	for (int i=2; i<=n; i++){
		while (A[i-2])
			std::cout << i << " " ;
	}

	std::cout << std::endl;
}

int main(){
	int i, N;
	bool * A = new bool[N-2];

	std::cout << "Please enter N:\n";
	std::cin >> N;
	
	sieve(N, A);

	print_primes(N, A);
	
	return 0;
	delete[] A;
	
}

