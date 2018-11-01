#include <iostream>

//TODO #1.1: add a function prototype for fib
uint fib( uint );

//TODO #2.1: add a function prototype for fact
uint fact( uint );

int main()
{
	//TODO: #1.2 call your fib function, print the result
	std::cout << "\n This is fib( 10 ): " << fib( 10 );

	//TODO: #2.2 call your fact function, print the result
	std::cout << "\n This is fact( 10 ): " << fact( 10 );

	return 0;
}

//TODO #2.3: add your recursive fib function from class
uint fib( uint n ){
	if( n == 0 || n == 1 ){
		return n;
	}

	return fib( n - 1 ) + fib( n - 2 );
}

//TODO #2.4: add your recursive fact function from class
uint fact( uint n ){
	if( n == 0 ) return 1;

	return n * fact( n - 1 );
}