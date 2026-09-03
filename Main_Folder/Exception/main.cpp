#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>
#include <sstream>

// Exception fundamentals added and commented:
// - throwing standard exceptions (std::invalid_argument)
// - translating exceptions (wrap lower-level exception in higher-level type)
// - nesting exceptions with std::throw_with_nested and inspecting them with std::rethrow_if_nested
// - noexcept usage (promise a function won't throw)
// - class example showing public/private members and function-try-block in constructor and member function

// Custom exception type (derives from std::runtime_error)
struct MyException : std::runtime_error {
    using std::runtime_error::runtime_error; // inherit constructors
};

// Basic function that may throw on error (division by zero)
int divide(int a, int b) {
    if (b == 0) {
        // throw a standard library exception to indicate invalid argument
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

// Wrapper that demonstrates translating and nesting exceptions.
// It calls divide(), and if divide throws we translate that error into
// MyException while preserving the original exception as nested information.
int performDivision(int a, int b) {
    try {
        return divide(a, b);
    } catch (...) {
        // translate and nest the original exception for later inspection
        std::throw_with_nested(MyException("performDivision failed"));
    }
}

// Example of a noexcept function: the compiler will call std::terminate
// if this function emits an exception. Mark functions noexcept only when
// you guarantee they won't throw.
int identity_noexcept(int x) noexcept {
    return x; // safe, will not throw
}

// Helper to print nested exception chain (if any)
void printNested(const std::exception& e) {
    std::cerr << "  cause: " << e.what() << '\n';
    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& nested) {
        printNested(nested);
    } catch (...) {
        std::cerr << "  cause: (unknown non-std exception)\n";
    }
}

// ---------------------------------------------------------------------------
// Class-based example showing public/private members and function-try-block
// - private: internal state and helper that may throw
// - public: constructor (function-try-block) and member function (function-try-block)
// Function-try-block syntax allows catching exceptions thrown during the
// entire function (including initialization list and body) and handling them.
// ---------------------------------------------------------------------------
class SafeCalculator {
private:
    int lastResult_;

    // private helper may throw - demonstrates encapsulation of error-prone logic
    void validateDenominator(int b) {
        if (b == 0) throw std::invalid_argument("denominator cannot be zero");
    }

public:
    // Constructor uses a function-try-block to catch exceptions thrown during
    // initialization or in the constructor body. This is useful for adding
    // context or logging before propagating the error.
    SafeCalculator(const std::string& cfg) try : lastResult_(0) {
        // simulate configuration parsing that might fail
        if (cfg == "bad") throw std::runtime_error("invalid configuration");
    } catch (const std::exception& e) {
        std::cerr << "SafeCalculator ctor caught: " << e.what() << '\n';
        // option: translate the exception, add context, or rethrow
        throw; // rethrow after logging
    }

    // Member function with function-try-block. It can catch and handle
    // specific exceptions thrown anywhere in the function body.
    int divideAndStore(int a, int b) try {
        validateDenominator(b);        // may throw
        lastResult_ = a / b;           // may throw if other errors occur
        return lastResult_;
    } catch (const std::invalid_argument& e) {
        std::cerr << "SafeCalculator::divideAndStore handled: " << e.what() << '\n';
        throw; // decide to rethrow after handling/logging
    } catch (const std::exception& e) {
        std::cerr << "SafeCalculator::divideAndStore unexpected: " << e.what() << '\n';
        throw; // rethrow
    }

    int lastResult() const noexcept { return lastResult_; }
};

int main() {
    // 1) Direct use: catch the specific exception thrown by divide()
    try {
        int r = divide(10, 0);
        std::cout << "divide result: " << r << '\n';
    } catch (const std::invalid_argument& ex) {
        // catch the specific type; good practice when you can handle it
        std::cerr << "Caught invalid_argument: " << ex.what() << '\n';
    }

    // 2) Using performDivision which nests exceptions
    try {
        int r2 = performDivision(10, 0);
        std::cout << "performDivision result: " << r2 << '\n';
    } catch (const MyException& e) {
        // handle the translated (higher-level) exception
        std::cerr << "Caught MyException: " << e.what() << '\n';
        // inspect nested cause(s)
        printNested(e);
    } catch (const std::exception& e) {
        // fallback for other std exceptions
        std::cerr << "Std exception: " << e.what() << '\n';
    } catch (...) {
        // catch-all: rarely useful except for logging or cleanup
        std::cerr << "Unknown non-std exception caught\n";
    }

    // 3) Demonstrate rethrowing: catch, log, then rethrow to caller
    try {
        try {
            throw std::runtime_error("low-level failure");
        } catch (const std::exception& e) {
            std::cerr << "Log and rethrow: " << e.what() << '\n';
            throw; // rethrow the same exception object
        }
    } catch (const std::exception& e) {
        std::cerr << "Caught after rethrow: " << e.what() << '\n';
    }

    // 4) noexcept example (no output expected unless it throws -> terminate)
    std::cout << "identity_noexcept(5) = " << identity_noexcept(5) << '\n';

    // 5) catch-all example (last resort)
    try {
        // simulate throwing a primitive or unknown type or msg
        throw "salut";
    } catch (int code) {
        std::cerr << "Caught primitive exception with code: " << code << '\n';
    }
    catch (const char* msg) {
        std::cerr << "Caught string exception: " << msg << '\n';
    } catch (...) {
        std::cerr << "Caught unknown exception type\n";
    }

    // -----------------------------------------------------------------------
    // Use the class-based example (public/private + function-try-block)
    // -----------------------------------------------------------------------
    try {
        SafeCalculator sc("bad"); // constructor will throw and be handled in ctor try-block
    } catch (const std::exception& e) {
        std::cerr << "Main caught ctor failure: " << e.what() << '\n';
    }

    try {
        SafeCalculator sc("good");
        try {
            sc.divideAndStore(10, 0); // will be handled inside function-try-block then rethrown
        } catch (const std::exception& e) {
            std::cerr << "Main caught divide failure: " << e.what() << '\n';
        }
        // successful call
        int r = sc.divideAndStore(20, 4);
        std::cout << "SafeCalculator lastResult = " << sc.lastResult() << " (returned " << r << ")\n";
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error in SafeCalculator usage: " << e.what() << '\n';
    }

    return 0;
}


