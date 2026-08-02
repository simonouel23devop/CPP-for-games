#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <thread>
#include <chrono>

int main() {
	// Variables to store user's name and age
	std::string name;
	int age;

	std::cout << "\033[36m" << "Welcome to the access control system 1.0. (W.A.C.S) " << "\033[0m" << std::endl;
	std::cout << "\033[36m" << "--------------------------------------------------- " << "\033[0m" << std::endl;
	std::cout << "" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "" << std::endl;
	std::cout << "\033[32m" << "Memory core loaded...." <<  std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "System initialized...." <<  std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Keyboard functionality initialized...." <<  std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Interface standby...." << "\033[0m" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;



	const int maxAttempts = 3;
	for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
		// Ask for user's name
		std::cout << "\033[37m" << "Enter your name: " << "\033[0m";	
		std::getline(std::cin, name);

		// If name is empty (possible if previous extraction left a newline), read again
		if (name.empty()) {
			std::getline(std::cin, name);
		}

		// Ask for user's age
		std::cout << "\033[37m" << "Enter your age: " << "\033[0m";
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
			std::cout << "" << std::endl;
			std::cout << "Access granted, welcome! " << name << "." << std::endl;
			return 0;
		} else {
			std::cout << "" << std::endl;
			std::cout << "Error: access denied." << std::endl;
			if (attempt < maxAttempts) {
				std::cout << "" << std::endl;
				std::cout << "Please try again (" << (maxAttempts - attempt) << " attempts left)." << std::endl;
			}
		}
	}
	std::cout << "" << std::endl;
	std::cout << "Maximum attempts reached. Access denied." << std::endl;
	return 1;
}
