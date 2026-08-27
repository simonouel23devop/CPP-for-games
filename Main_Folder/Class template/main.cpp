// Demonstration of a class template to print the binary representation
// of integral values. We use a class template so the same implementation
// can handle any integral type (signed/unsigned, different widths)
// without duplicating code and with compile-time type-safety.

#include <iostream>
#include <type_traits>
#include <stdexcept>

template<typename T> // typename T
class BinaryPrinter {
public:
	// Construct with a value to allow both printing and indexed access.
	// Uses std::make_unsigned_t to ensure bitwise shifts are defined
	explicit BinaryPrinter(T value)
		: value_(static_cast<std::make_unsigned_t<T>>(value)) {}

	// Print the binary representation of the stored value.
	void print() const {
		constexpr std::size_t bits = sizeof(T) * 8;

		
		std::cout << "0b";
		for (std::size_t i = 0; i < bits; ++i) {
			std::size_t shift = bits - 1 - i;
			std::cout << ((value_ >> shift) & 1);
		}
		std::cout << '\n';
	}

	// Subscript operator: returns the bit at position pos (0 == least significant bit).
	// We choose LSB-based indexing because it's the most common when manipulating bits..
	bool operator[](std::size_t pos) const {
		constexpr std::size_t bits = sizeof(T) * 8;
		if (pos >= bits) {
			throw std::out_of_range("bit index out of range");
		}
		return static_cast<bool>((value_ >> pos) & 1u);
	}

private:
	std::make_unsigned_t<T> value_;
};

// Full specialization for bool: it's convenient to treat bool as a single-bit
// value and provide a lightweight implementation.
template<>
class BinaryPrinter<bool> {
public:
	explicit BinaryPrinter(bool value)
		: value_(value) {}

	void print() const {
		std::cout << "0b" << (value_ ? '1' : '0') << '\n';
	}

	bool operator[](std::size_t pos) const {
		if (pos != 0) {
			throw std::out_of_range("bit index out of range for bool");
		}
		return value_;
	}

private:
	bool value_;
};

// alias template improves readability//
template<typename T>
using BinPrinter = BinaryPrinter<T>; // typename T

// Explicit template instantiation: force the compiler to instantiate the
// template (and emit the necessary code) for these commonly-used types in
// here (useful when splitting declarations/definitions across files).
template class BinaryPrinter<unsigned int>;
template class BinaryPrinter<long long>;
template class BinaryPrinter<bool>;

int main() {
	unsigned int a = 13u;
	long long b = -5LL;

	// Use the template for different integral types
	std::cout << "unsigned int (13) in binary: ";
	// Use the alias template for brevity; create an instance so we can also index bits
	BinPrinter<unsigned int> pa(a);
	pa.print();
	std::cout << "bit 0 (LSB) of 13: " << pa[0] << '\n';

	std::cout << "long long (-5) in binary:     ";
	BinaryPrinter<long long> pb(b);
	pb.print();
	std::cout << "sign bit (MSB) of -5: " << pb[sizeof(long long) * 8 - 1] << '\n';

	return 0;
}
