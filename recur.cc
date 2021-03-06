#include <iostream>
#include "recur_test.h"

// added mult
uint mult( uint );
uint fib( uint );
uint fact( uint );

//tests
void fib_test();
void fact_test();
void mult_test();

int main()
{
	// automated testing
	Test tests[] = {
		{ "fibonacci", &fib_test },
		{ "factorial", &fact_test },
		{ "mult", &mult_test },
	};

	for( auto t : tests ){
		t.Run();
//		if( !testing::passed ) break;
	}

	return 0;
}

// mult
uint mult( uint m, uint n ){
	if( n == 0 ) return 0;
	if( n == 1 ) return m;

	--n;
	return m + mult( m, n );
}

void mult_test() {
	struct testObj {
		std::string name;
		uint m;
		uint n;
		uint result;
	};

	testObj table[] = {
		{	.name = "five times five",
			.m = 5,
			.n = 5,
			.result = 25,
		},
		{	.name = "five times zero",
			.m = 5,
			.n = 0,
			.result = 0,
		},
		{	.name = "zero times five",
			.m = 0,
			.n = 5,
			.result = 0,
		},
		{	.name = "fib-complex",
			.m = fib( 35 ),
			.n = 1,
			.result = 9227465,
		},
/*		{	.name = "fib-complex crash",
			.m = 0,
			.n = fib( 35 ),
			.result = 0,
		},
*/	};

	for( auto t : table ){
		Expect( t.name, t.result, mult( t.m, t.n ));
	}
}

// fibonacci
uint fib( uint n ){
	if( n == 0 || n == 1 ){
		return n;
	}

	return fib( n - 1 ) + fib( n - 2 );
}

// factorial
uint fact( uint n ){
	if( n == 0 ) return 1;

	return n * fact( n - 1 );
}

// tests
void fib_test() {
	struct testObj {
		std::string name;
		uint n;
		uint result;
	};

	testObj table[] {
		{	.name = "zero",
			.n = 0,
			.result = 0,
		},
		{	.name = "one",
			.n = 1,
			.result = 1,
		},
		{	.name = "sixth term",
			.n = 6,
			.result = 8,
		},
		{	.name = "large term",
			.n = 35,
			.result = 9227465,
		},
/*		{	.name = "too big to compute"
			.n = 50,
			.result = 0,
		}
*/	};

	for( auto t : table ){
		Expect( t.name, t.result, fib( t.n ));
	}
}

void fact_test() {
	struct testObj {
		std::string name;
		uint n;
		uint result;
	};

	testObj table[] {
		{	.name = "zero",
			.n = 0,
			.result = 1,
		},
		{	.name = "one",
			.n = 1,
			.result = 1,
		},
		{	.name = "five",
			.n = 5,
			.result = 120,
		},
		{	.name = "six with typo",
			.n = 6,
			.result = 270,
		},
	};

	for( auto t : table ){
		Expect( t.name, t.result, fact( t.n ));
	}
}