#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

// anonymous namespace is accessible only in this translation unit
// so - only this header and any file that includes it
namespace {
	// persistent test truth variable
	namespace testing {
		bool passed = true;
	}

	// formatted styles of text for terminal output
	namespace textStyle {
		std::string ok = "\e[1;32m";
		std::string fail = "\e[1;31m";
		std::string stealth = "\e[30m";
		std::string title = "\e[1m";
		std::string reset = "\e[0m";
	}	
}

// EXPECT
// Swiss-army comparison function
// usage similar to assert() but doesn't kill process
// equality is stealthy, inequalilty is verbose
template< typename T, typename U >
void Expect( std::string file, int line, std::string name, T wanted, U got ){
	if( wanted != got ){
		std::cout
			<< textStyle::title
			<< "\n    ->  " << name << textStyle::reset
			<< textStyle::stealth
			<< "\n     -  " << "wanted  " << textStyle::reset << wanted
			<< textStyle::stealth
			<< "\n     -  " << "got     " << textStyle::reset << got
			<< textStyle::stealth
			<< "\n     @  " << file << ":" << line << textStyle::reset
			<< "\n";

		testing::passed = false;
		return;
	}
}

// Now define any call to expand with a macro (I know, bleh) to include file and line
#define Expect(...) Expect( __FILE__, __LINE__, __VA_ARGS__ )

// TEST CLASS
class Test {
public:
	Test( std::string, void( * )() ); // name and pointer to test function

	void Run(); // runs the test

private:
	std::string name_;
	void( *exec_ )();
	int index; // "Test::index of Test::count"
	static int count; // track how many tests have been instantiated

	std::chrono::duration<double> elapsed_;
};
int Test::count( 0 ); // sets # of Tests to 0

Test::Test( std::string name, void( *exec )() ){
	count++;
	index = count;

	name_ = name;
	exec_ = exec;
};

// Wraps the test exec function in a layer to track:
// pass / fail
// time elapsed
void Test::Run() {
	// Test label
	std::cout
		<< "\n " << textStyle::stealth << index << "/" << count << textStyle::reset
		<< " " << textStyle::title << name_ << textStyle::reset
		<< "\n";

	// reset testing::passed, set start time, execute test, set end time, calc duration
	testing::passed = true;
	auto start = std::chrono::high_resolution_clock::now();
	exec_(); 
	auto end = std::chrono::high_resolution_clock::now();
	elapsed_ = end - start;

	// result output
	std::cout << "\n\t";

	if( testing::passed )
		std::cout << textStyle::ok << "pass" << textStyle::reset;
	else
		std::cout << textStyle::fail << "fail" << textStyle::reset;

	std::cout
		<< std::fixed << std::setprecision( 2 )
		<< " " << textStyle::stealth << elapsed_.count() << "s" << textStyle::reset
		<< "\n";

	return;
}

// ERRORFOO
// easy-to-inherit error interface
class errorFoo {
public:
	void setErr( std::string error ) { if( error_ == "" ) error_ = error; }
	std::string getErr() { return error_; }
	void flushErr(){ error_ = ""; }
	bool err() { return ( error_ != "" ); }
private:
	std::string error_;
};