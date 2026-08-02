#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

int main() {
	// Variables to store user's name and age
	std::string name;
	int age;


	const int maxAttempts = 3;
	for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
		// Ask for user's name
		std::cout << "Enter your name: ";	
		std::getline(std::cin, name);

		// If name is empty (possible if previous extraction left a newline), read again
		if (name.empty()) {
			std::getline(std::cin, name);
		}

		// Ask for user's age
		std::cout << "Enter your age: ";
		if (!(std::cin >> age)) {
			std::cout << "Invalid age input." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (attempt < maxAttempts) {
				std::cout << "Please try again (" << (maxAttempts - attempt) << " attempts left)." << std::endl;
				continue;
			} else {
				std::cout << "Maximum attempts reached. Access denied." << std::endl;
				return 1;
			}
		}

		// Clear rest of the line after reading age
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// Normalize name to lowercase for a case-insensitive comparison
		std::string lower_name = name;
		std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
					   [](unsigned char c){ return std::tolower(c); });

		// Grant access only if name is "simon" (case-insensitive) AND age is 39
		if (lower_name == "simon" && age == 39) {
			std::cout << "Access granted, welcome! " << name << "." << std::endl;
			return 0;
		} else {
			std::cout << "Error: access denied." << std::endl;
			if (attempt < maxAttempts) {
				std::cout << "Please try again (" << (maxAttempts - attempt) << " attempts left)." << std::endl;
			}
		}
	}

	std::cout << "Maximum attempts reached. Access denied." << std::endl;
	return 1;
}
