#include <iostream>
#include <limits>

int main() {
	// Example 1: else-if ladder to determine letter grade from a numeric score
	int score = 0;
	std::cout << "Enter exam score (0-100): ";
	if (!(std::cin >> score)) {
		std::cerr << "Invalid input" << std::endl;
		return 1;
	}

	char grade;
	if (score >= 90) {
		grade = 'A';
	} else if (score >= 80) {
		grade = 'B';	
	} else if (score >= 70) {
		grade = 'C';
	} else if (score >= 60) {
		grade = 'D';
	} else {
		grade = 'F';
	}

	std::cout << "Score " << score << " -> Grade " << grade << std::endl;

	// Clear any leftover input
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Example 2: switch-case to handle a simple menu
	int choice = 0;
	std::cout << "\nMenu:\n";
	std::cout << "1) Start game\n";
	std::cout << "2) Options\n";
	std::cout << "3) Credits\n";
	std::cout << "4) Quit\n";
	std::cout << "Enter choice (1-4): ";

	if (!(std::cin >> choice)) {
		std::cerr << "Invalid input" << std::endl;
		return 1;
	}

	switch (choice) {
		case 1:
			std::cout << "Starting game..." << std::endl;
			break;
		case 2:
			std::cout << "Opening options..." << std::endl;
			break;
		case 3:
			std::cout << "Showing credits..." << std::endl;
			break;
		case 4:
			std::cout << "Quitting. Goodbye!" << std::endl;
			break;
		default:
			std::cout << "Invalid choice" << std::endl;
			break;
	}

	// --- Loop examples ---

	// For loop: print numbers 1 to 5
	std::cout << "\nFor loop: ";
	for (int i = 1; i <= 5; ++i) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	// While loop: simple countdown
	int countdownStart = 0;
	std::cout << "\nEnter a positive number for countdown (0 to skip): ";
	if (std::cin >> countdownStart && countdownStart > 0) {
		while (countdownStart > 0) {
			std::cout << countdownStart << " ";
			--countdownStart;
		}
		std::cout << "\nCountdown finished." << std::endl;
	} else {
		// clear error state if input was invalid
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cout << "Skipping countdown." << std::endl;
	}

	// Do-while loop: ask user if they want to repeat a message
	char again = 'n';
	do {
		std::cout << "\nThis is a do-while loop. Do you want to see it again? (y/n): ";
		std::cin >> again;
		// normalize
		if (again == 'y' || again == 'Y') {
			std::cout << "You chose to repeat.\n";
		}
	} while (again == 'y' || again == 'Y');

	std::cout << "Program finished." << std::endl;

	return 0;
}
