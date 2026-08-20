#include <iostream>
#include <cmath>

// Add two integers using pointers to the operands
int add_ptr(const int* a, const int* b) {
	if (!a || !b) return 0; // simple null check
	return (*a) + (*b);
}

// Add two integers using pointers and store the result through an output pointer
void add_into(const int* a, const int* b, int* out) {
	if (!a || !b || !out) return;
	*out = (*a) + (*b);
}

// Compute power using pointers: returns base^exp
double pow_ptr(const double* base, const double* exp) {
	if (!base || !exp) return 1.0;
	return std::pow(*base, *exp);
}

// Compute power using pointers and store the result through an output pointer
void pow_into(const double* base, const double* exp, double* out) {
	if (!base || !exp || !out) return;
	*out = std::pow(*base, *exp);
}

int main() {
	int a = 5;
	int b = 10;

	// Example 1: function returning the sum, operands passed by pointer
	int sum = add_ptr(&a, &b);
	std::cout << "add_ptr(&a, &b) = " << sum << std::endl;

	// Example 2: function that writes the result through an output pointer
	int result = 0;
	add_into(&a, &b, &result);
	std::cout << "add_into(&a, &b, &result) -> result = " << result << std::endl;

	// Power examples
	double base = 2.0;
	double exponent = 8.0;

	double p = pow_ptr(&base, &exponent);
	std::cout << base << "^" << exponent << " = " << p << std::endl;

	double out = 0.0;
	pow_into(&base, &exponent, &out);
	std::cout << "pow_into(&base, &exponent, &out) -> out = " << out << std::endl;

	return 0;
}
