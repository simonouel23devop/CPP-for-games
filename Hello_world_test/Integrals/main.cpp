#include <iostream>
#include <cstdint>


int main()

{
	
	int min_int = -2147483648; // Minimum value for a 32-bit signed integer (8bits x 4  = 4 bytes = 32 bits)
	int max_int = 2147483647;  // Maximum value for a 32-bit signed integer (8bits x 4  = 4 bytes = 32 bits)

	unsigned int min_uint = 0; // Minimum value for a 32-bit unsigned integer (8bits x 4  = 4 bytes = 32 bits)
	//unsigned int max_uint = 4294967295; // Maximum value for a 32-bit unsigned integer
	unsigned int max_uint = -1; // Maximum value for a 32-bit unsigned integer (8bits x 4  = 4 bytes = 32 bits)


	std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
	std::cout << "Size of unsigned int (-1): " << max_uint << " bytes" << std::endl;

	short max_short = 32767; // Maximum value for a 16-bit signed integer (8bits x 2  = 2 bytes = 16 bits)
	short min_short = -32768; // Minimum value for a 16-bit signed integer (8bits x 2  = 2 bytes = 16 bits)
	
	unsigned short max_ushort = 0xFFFFF; // Maximum value for a 16-bit unsigned integer (8bits x 2  = 2 bytes = 16 bits)
	unsigned short min_ushort = 0; // Minimum value for a 16-bit unsigned integer (8bits x 2  = 2 bytes = 16 bits)

	std::cout << "Size of short: " << sizeof(short) << " bytes" << std::endl;

	long max_long = 2147483647; // Maximum value for a 32-bit signed integer (8bits x 4  = 4 bytes = 32 bits)
	long min_long = -2147483648; // Minimum value for a 32-bit signed integer (8bits x 4  = 4 bytes = 32 bits)

	long long max_longlong = 9223372036854775807; // Maximum value for a 64-bit signed integer (8bits x 8  = 8 bytes = 64 bits)
	long long min_longlong = -9223372036854775807; // Minimum value for a 64-bit signed integer (8bits x 8  = 8 bytes = 64 bits)

	std::int32_t i = 0; // Always a32-bit signed integer
	std::uint32_t ui = 0; // Always a 32-bit unsigned integer

	std::int16_t i16 = 0; // Always a 16-bit signed integer
	std::uint16_t ui16 = 0; // Always a 16-bit unsigned integer

	std::int64_t i64 = 0; // Always a 64-bit signed integer
	std::uint64_t ui64 = 0; // Always a 64-bit unsigned integer

	std::cout << "Size of size_t: " << sizeof(size_t) << " bytes" << std::endl;



	return 0;
}
