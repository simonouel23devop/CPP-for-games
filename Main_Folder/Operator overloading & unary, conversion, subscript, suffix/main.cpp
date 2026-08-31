#include <iostream>
#include <utility> // for std::move
#include <stdexcept> // for std::out_of_range
#include <cmath> 
#include <string>


    class Point {
    private:
     int x, y;

    public:
        // Default constructor
        Point() : x(0), y(0) {}

        // Parameterized constructor
        Point(int x, int y) : x(x), y(y) {}

        // Overloaded assignment operator for Point
        // Allows assigning one Point to another (handles self-assignment)
        Point& operator=(const Point& other) {
            if (this != &other) {
                this->x = other.x;
                this->y = other.y;
            }
            std::cout << "Point copy assign: this=" << this << ", other=" << &other << std::endl;
            return *this;
        }



        // Comparison operators for Point
        // Provides logical equality semantics (needed for comparing values)
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Point& other) const {
            return !(*this == other);
        }

        // Copy constructor
        Point(const Point& other) : x(other.x), y(other.y) {
            std::cout << "Point copy ctor: this=" << this << ", other=" << &other << std::endl;
        }

        // Move constructor
        Point(Point&& other) noexcept : x(other.x), y(other.y) {
            std::cout << "Point move ctor: this=" << this << ", other=" << &other << std::endl;
            other.x = 0; other.y = 0; // leave moved-from in a valid state
        }

        // Move assignment
        Point& operator=(Point&& other) noexcept {
            if (this != &other) {
                this->x = other.x;
                this->y = other.y;
                other.x = 0; other.y = 0;
            }
            std::cout << "Point move assign: this=" << this << ", other=" << &other << std::endl;
            return *this;
        }

     // Declare the global function as a friend to access private members
     friend std::ostream& operator<<(std::ostream& os, const Point& p);
    };

// (User-defined literal moved below Vector2D definition)

    // Definition of the non-member overloaded '<<' operator
    std::ostream& operator<<(std::ostream& os, const Point& p) {
      os << "(" << p.x << ", " << p.y << ")";
     return os; // Return the stream to allow chaining (e.g., cout << p1 << p2;)
    }




    class Vector2D {
    public:
        double x, y;

        Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

        // Overloading the '+' operator
        Vector2D operator+(const Vector2D& other) const {
            return Vector2D(this->x + other.x, this->y + other.y);
        }

        // Unary negation operator
        // Allows writing -v to get a vector pointing in the opposite direction.
        // Useful for reversing direction, simplifying expressions, and making
        // intent clearer in arithmetic code (e.g., v = -u + w;).
        Vector2D operator-() const {
            return Vector2D(-x, -y);
        }

        // Array subscript operator
        // Allows accessing components by index like v[0] for x and v[1] for y. Array
        // This makes the Vector2D behave like a small fixed-size array and
        // improves interoperability with algorithms that use indexing.
        // We provide both const and non-const overloads and throw on invalid index.
        double& operator[](std::size_t idx) {
            if (idx == 0) return x;
            if (idx == 1) return y;
            throw std::out_of_range("Vector2D index out of range");
        }

        const double& operator[](std::size_t idx) const {
            if (idx == 0) return x;
            if (idx == 1) return y;
            throw std::out_of_range("Vector2D index out of range");
        }

        // Overloading the assignment operator
        // This allows assigning one Vector2D to another (e.g., v4 = v3).
        // It performs a self-assignment check and returns * pointer this to allow
        // chained assignments like a = b = c;
        Vector2D& operator=(const Vector2D& other) {
            if (this != &other) {
                this->x = other.x;
                this->y = other.y;
            }
            std::cout << "Vector2D copy assign: this=" << this << ", other=" << &other << std::endl;
            return *this;
        }

        // Copy constructor
        Vector2D(const Vector2D& other) : x(other.x), y(other.y) {
            std::cout << "Vector2D copy ctor: this=" << this << ", other=" << &other << std::endl;
        }

        // Move constructor
        Vector2D(Vector2D&& other) noexcept : x(other.x), y(other.y) {
            std::cout << "Vector2D move ctor: this=" << this << ", other=" << &other << std::endl;
            other.x = 0.0; other.y = 0.0;
        }

        // Move assignment to another.
        Vector2D& operator=(Vector2D&& other) noexcept {
            if (this != &other) {
                this->x = other.x;
                this->y = other.y;
                other.x = 0.0; other.y = 0.0;
            }
            std::cout << "Vector2D move assign: this=" << this << ", other=" << &other << std::endl;
            return *this;
        }

        // Comparison operators for Vector2D
        // Use an epsilon to compare floating-point components to avoid false negatives
        bool operator==(const Vector2D& other) const {
            static constexpr double EPS = 1e-9;
            return std::fabs(x - other.x) < EPS && std::fabs(y - other.y) < EPS;
        }

        bool operator!=(const Vector2D& other) const {
            return !(*this == other);
        }




    };


// User-defined literal for Vector2D
// Allows creating vectors with a concise literal syntax from string literals,
// The literal parses two comma-separated numbers from the string literal.
inline Vector2D operator"" _v(const char* str, std::size_t len) {
    std::string s(str, len);
    auto pos = s.find(',');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Vector literal must be in format 'x,y'");
    }
    double a = std::stod(s.substr(0, pos));
    double b = std::stod(s.substr(pos + 1));
    return Vector2D(a, b);
}

     // overload operator +
    int main() {
        Vector2D v1(2.0, 3.0);
        Vector2D v2(1.5, 4.5);

        // Using the overloaded '+' operator
        Vector2D v3 = v1 + v2;

        std::cout << "v3: (" << v3.x << ", " << v3.y << ")\n"; // Output: v3: (3.5, 7.5)


        // Use the assignment operator to copy v3 into v4
        Vector2D v4;
        v4 = v3; // calls Vector2D::operator=
        std::cout << "v4 (after assignment): (" << v4.x << ", " << v4.y << ")\n";




        Point p1(15, 20);
        std::cout << "Address of p1: " << &p1 << std::endl;
        // Use default constructor and assignment operator for Point
        Point p2; // default-constructed at (0,0)
        p2 = p1; // calls Point::operator=
        std::cout << "Address of p2: " << &p2 << std::endl;

        // Demonstrate copy and move for Point
        Point p3 = p1; // copy constructor
        std::cout << "p3 (copy) address: " << &p3 << ", value: " << p3 << std::endl;
        Point p4 = std::move(p1); // move constructor
        std::cout << "p4 (moved) address: " << &p4 << ", value: " << p4 << std::endl;
        // Custom print syntax
        std::cout << "The point is: " << p1 << std::endl;
        std::cout << "p2 (after assignment): " << p2 << std::endl;

        // Demonstrate copy and move for Vector2D //
        Vector2D v5 = v3; // copy constructor
        std::cout << "v5 (copy) address: " << &v5 << ", value: (" << v5.x << ", " << v5.y << ")\n";
        Vector2D v6 = std::move(v3); // move constructor
        std::cout << "v6 (moved) address: " << &v6 << ", value: (" << v6.x << ", " << v6.y << ")\n";
        // Demonstrate unary negation operator
        Vector2D vneg = -v4; // calls Vector2D::operator-()
        std::cout << "vneg (unary - on v4): (" << vneg.x << ", " << vneg.y << ")\n";
        // Demonstrate array subscript operator
        std::cout << "v4[0] = " << v4[0] << ", v4[1] = " << v4[1] << std::endl;
        // Modify components using subscript operator via array.
        v4[0] = -7.7; v4[1] = 8.8;
        std::cout << "v4 (after subscript assignment): (" << v4[0] << ", " << v4[1] << ")\n";
        // Demonstrate comparison operators
        std::cout << std::boolalpha;
        // Demonstrate user-defined literal for Vector2D
        Vector2D vlit = "7.7,8.8"_v; // uses operator"" _v
        std::cout << "vlit (UDL) address: " << &vlit << ", value: (" << vlit.x << ", " << vlit.y << ")\n";
       
        return 0;
        
    }



  

 