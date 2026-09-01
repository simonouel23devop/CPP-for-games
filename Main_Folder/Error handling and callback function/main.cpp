#include <iostream>
#include <functional>
#include <string>

// Traditional error handling example using:
// - bool return value for success/failure
// - an ErrorCode enum handled via switch
// - a callback (std::function) to report errors to the caller

enum class ErrorCode {
	None = 0,
	FileNotFound = 1,
	InvalidInput = 2,
	PermissionDenied = 3,
	Unknown = 99
};

// processData simulates an operation that may fail for a few reasons.
// It returns bool to indicate overall success. When an error occurs it
// sets outError and calls the onError callback so the caller can decide
// how to log or display the error (decoupled reporting).
bool processData(const std::string& filename,
				 int value,
				 std::function<void(ErrorCode)> onError,
				 ErrorCode& outError) {
	if (filename.empty()) {
		outError = ErrorCode::FileNotFound;
		if (onError) onError(outError);
		return false;
	}

	if (value < 0) {
		outError = ErrorCode::InvalidInput;
		if (onError) onError(outError);
		return false;
	}

	// Simulate permission problem for a specific filename
	if (filename == "secret.txt") {
		outError = ErrorCode::PermissionDenied;
		if (onError) onError(outError);
		return false;
	}

	outError = ErrorCode::None;
	return true;
}
int main() {
	// Simple handler: prints failures to stdout
	auto errorHandler = [](ErrorCode code) {
		switch (code) {
			case ErrorCode::None: break;
			case ErrorCode::FileNotFound:    std::cout << "[FAIL] File not found\n"; break;
			case ErrorCode::InvalidInput:    std::cout << "[FAIL] Invalid input\n"; break;
			case ErrorCode::PermissionDenied:std::cout << "[FAIL] Permission denied\n"; break;
			default: std::cout << "[FAIL] Unknown error (code=" << static_cast<int>(code) << ")\n"; break;
		}
	};

	ErrorCode code;

	// Examples: show immediate output when callbacks are invoked
	bool ok = processData("", 42, errorHandler, code); // FileNotFound
	std::cout << "processData returned: " << (ok ? "success" : "failure") << "\n";

	ok = processData("data.txt", -1, errorHandler, code); // InvalidInput
	std::cout << "processData returned: " << (ok ? "success" : "failure") << "\n";

	ok = processData("secret.txt", 10, errorHandler, code); // PermissionDenied
	std::cout << "processData returned: " << (ok ? "success" : "failure") << "\n";

	ok = processData("data.txt", 10, errorHandler, code); // success
	std::cout << "processData returned: " << (ok ? "success" : "failure") << "\n";

	// Applied example: an application component that collects errors
	struct App {
		int errorCount = 0;

		// member handler increments error count and prints a prefixed message
		void handleError(ErrorCode code) {
			switch (code) {
				case ErrorCode::None: return;
				case ErrorCode::FileNotFound:    std::cout << "[APP] file missing\n"; break;
				case ErrorCode::InvalidInput:    std::cout << "[APP] invalid input\n"; break;
				case ErrorCode::PermissionDenied:std::cout << "[APP] no permission\n"; break;
				default: std::cout << "[APP] unknown (" << static_cast<int>(code) << ")\n"; break;
			}
			++errorCount;
		}

		void run() {
			ErrorCode e;
			// bind member function to create a callback compatible with processData
			auto cb = std::bind(&App::handleError, this, std::placeholders::_1);

			processData("config.txt", 5, cb, e);      // likely success
			processData("", 5, cb, e);                // file not found -> increments errorCount
			processData("data.txt", -10, cb, e);     // invalid input -> increments errorCount
		}
	} app;

	app.run();
	std::cout << "App errorCount=" << app.errorCount << "\n";

	return 0;
}
