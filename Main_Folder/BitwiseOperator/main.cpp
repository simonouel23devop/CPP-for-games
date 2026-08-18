#include <iostream>
#include <cstdint>
#include <bitset>



// This program demonstrates the use of bitwise operations and masking in C++20.
int main() {
	

	// Use unsigned types for bitwise operations to avoid sign extension
	uint8_t a = 0b10010110; // 150 decimal	
	uint8_t b = 0b01101001; // 105 decimal
	uint8_t mask = 0b00000111; // 7 decimal

	// Print operands in binary and decimal
	std::cout << "a:     " << std::bitset<8>(static_cast<unsigned>(a)) << " (" << +a << ")" << std::endl;
	std::cout << "b:     " << std::bitset<8>(static_cast<unsigned>(b)) << " (" << +b << ")" << std::endl;
	std::cout << "mask:  " << std::bitset<8>(static_cast<unsigned>(mask)) << " (" << +mask << ")" << std::endl;

	// Addition (may exceed 8 bits) - use a wider type to hold the sum
	uint16_t sum = static_cast<uint16_t>(a) + static_cast<uint16_t>(b);
	std::cout << "sum:   " << std::bitset<16>(sum) << " (" << sum << ")" << std::endl;

	// Apply mask to the sum (promote mask to same width)
	uint16_t masked_sum = sum & static_cast<uint16_t>(mask);
	std::cout << "sum & mask: " << std::bitset<8>(static_cast<unsigned>(masked_sum)) << " (" << masked_sum << ")" << std::endl;

	// Also show (a + b + mask)
	uint16_t sum_with_mask = static_cast<uint16_t>(a) + static_cast<uint16_t>(b) + static_cast<uint16_t>(mask);
	std::cout << "a + b + mask: " << std::bitset<16>(sum_with_mask) << " (" << sum_with_mask << ")" << std::endl;

	return 0;
}
