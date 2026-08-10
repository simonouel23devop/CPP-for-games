#include <iostream>
#include <vector>

int main() {
    
	// Using auto to declare variables with different types.
	auto x = 10;
	auto y = 20.5;
	auto z = "Hello, World!";
	auto sum = x + y;


	
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;
    std::cout << "sum: " << sum << std::endl;

	// Using auto with a vector range.
	std::vector <int> vec = { 1, 2, 3, 4, 5,6,7,8,9,10 };
	
	// Using auto in a range-based for loop / increment with pointers.
	for (auto newvec = vec.begin(); newvec != vec.end(); ++newvec) {
		std::cout << *newvec << " Changed to newvec pointers. " << std::endl;
	}
	


    return 0;
}