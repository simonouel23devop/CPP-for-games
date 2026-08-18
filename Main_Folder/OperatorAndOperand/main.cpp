#include <iostream>


int main() {
	
	int a = 0, b = 0;

    std::cout << "Enter value for a: ";
    if (!(std::cin >> a)) {
        std::cerr << "Invalid input for a\n";
        return 1;
    }

    std::cout << "Enter value for b: ";
    if (!(std::cin >> b)) {
        std::cerr << "Invalid input for b\n";
        return 1;
    }

    // condition using the > operator
    if (a > b) {
        std::cout << "a > b" << std::endl;
    } else if (a == b) {
        std::cout << "a == b" << std::endl;
    } else {
        std::cout << "a < b" << std::endl;
    }

    // show the boolean result of the operand expression
    bool result = (a > b);
    std::cout << std::boolalpha << "(a > b) is " << result << std::endl;

    return 0;
}