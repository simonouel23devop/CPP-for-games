#include <iostream>




int main() {
	
	char c = 'A';
	char name[] = "Alice";

	signed char sc = 'A';
	unsigned char uc = 'A';


	wchar_t wc = L'A';


	std::cout << "sizeof(char): " << sizeof(c) << std::endl;
	std::cout << "sizeof(char[]): " << sizeof(name) << std::endl;
	std::cout << "sizeof(signed char): " << sizeof(sc) << std::endl;
	std::cout << "sizeof(unsigned char): " << sizeof(uc) << std::endl;
	std::cout << "sizeof(wchar_t): " << sizeof(wc) << std::endl;

	return 0;
}