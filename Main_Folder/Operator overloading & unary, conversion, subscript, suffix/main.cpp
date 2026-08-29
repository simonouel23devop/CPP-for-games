
// operator overloading //

#include <iostream>


    class Point {
    private:
     int x, y;

    public:
        Point(int x, int y) : x(x), y(y) {}

     // Declare the global function as a friend to access private members
     friend std::ostream& operator<<(std::ostream& os, const Point& p);
    };

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




    };


     // overload operator +
    int main() {
        Vector2D v1(2.0, 3.0);
        Vector2D v2(1.5, 4.5);

        // Using the overloaded '+' operator
        Vector2D v3 = v1 + v2;

        std::cout << "v3: (" << v3.x << ", " << v3.y << ")\n"; // Output: v3: (3.5, 7.5)




        Point p1(15, 20);
        // Custom print syntax
        std::cout << "The point is: " << p1 << std::endl;
        return 0;
        
    }



  

 