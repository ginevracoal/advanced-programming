
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


int main(){
	int count=1;
	int *array[100];
	int *primes[100];

	//initializing the array
	for(int i; i < 100; i++)
		*array[i] = i + 1;
	
	int i=2;
	*primes[0]=2;
	while(i < 100 && is_prime(*array[i])){
		primes[count] = array[i];
		std::cout << primes[count] << " \n";
		++i;
		++count;
	}

	return 0;
}

