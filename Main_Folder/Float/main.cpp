#include <iostream>


int main()
{

	// Integer float values

	float min_f = -3.4e38;
	float max_f = 3.4e38;

	double min_d = -1.7e308;
	double max_d = 1.7e308;

	long double min_ld = -1.7e308;
	long double max_ld = 1.7e308;


	// Boolean values

	bool t = true;
	bool f = false;

	bool is_true = (true);
	bool is_false = (!is_true);

	bool and_result = (is_true && is_false); // always be false

	std::cout << "Size of bool: " << sizeof(bool) << " bytes" << std::endl; // 1 byte = 8 bits

	return 0;
}