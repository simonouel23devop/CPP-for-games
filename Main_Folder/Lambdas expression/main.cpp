#include <iostream> 

// Templated function that takes two values of (possibly) different types
// and returns their sum. Template parameters are T and U.
template<typename T, typename U>
auto add(T x, U y) -> decltype(x + y) {
	return x + y;
}

int main() {

	// the lambda attribute :
	
	// f is a lambda that takes two ints and returns their sum.
	// The trailing return type '-> int' is optional here (the compiler can deduce it).
	auto f = [](int a, int b) -> int {return a + b; }; 

	int c = f(5, 10);

	// Use the templated add function directly
	auto s1 = add<int, int>(2, 3); // calls add with T=int, U=int
	std::cout << "add<int,int>(2,3): " << s1 << std::endl;

	// Generic lambda that forwards to the templated add function
	auto add_lambda = [](auto x, auto y) { return add(x, y); };
	auto s2 = add_lambda(2.5, 3); // adds double and int -> result is double
	std::cout << "add_lambda(2.5,3): " << s2 << std::endl;

	int a = 5;
	int b = 10;
	int e = 0;
	
	// Capture list: [=, &a, &b] means "capture everything by value, but capture a and b by reference".
	// In this case e is captured by value (its original value is used inside the lambda),
	// while a and b are captured by reference so later changes to them are observed.
	auto g = [=, &a, &b] { return e + a + b; }; // capture e by value, a and b by reference

	a = 10;
	b = 15;
	e = 5;

	int d = g(); // the auto variable g.

	std::cout << "g() :" << d << std::endl; 

	// Note: g captured a and b and e by value when it was created, so g() prints 25.

	return 0;
}