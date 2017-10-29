
/*
    Populate an array named primes containing the first prime numbers up to 100. Consider 2 as the first prime (i.e. primes[0] == 2).

        you are free to choose the design and the implementation.

        please comment and motivate your choices (e.g., allocate one big array, every time I find a new prime number I increase the size of the previous primes array, etc.)

Hints:

    The remainder of a division between two integers can be computed as follows:

int remainder = 6%3;

    Inside a for loop, you can use continue to immediately go to the next iteration, break to exit the loop. Note that if you have two or more nested loops, the statements affect only the innermost loop.

*/


#include <iostream>

//checks if a is a prime number
bool is_prime(int a){
	//int r;
	for(int d=2; d < a; d++){
		//r = a % d;
		if (a % d == 0){
			return false;
			break;
		} 
	}
	return true;
}

//prints the first n primes
void print_primes(int n, int primes[]){
	for(int i=1; i < n; i++){
 		std::cout << primes[i] << " ";
	}	
}

int main(){
	
	//counts prime numbers
	int count=1;

	//array containing prime numbers between 1 and 100
	int * primes = new int [100];

	//builds the array and counts the number of primes
	primes[0] = 2;
	for(int i=2; i <= 100; i++){
		if(is_prime(i)){
			primes[count] = i;		
			count++;
		}
	}

	//prints prime numbers 
	std::cout << "The first " << count << " prime numbers are: ";	
	print_primes(count, primes);
	std::cout << std::endl;

	//deallocates the memory
	delete[] primes;

	return 0;
}

