#include <iostream>

//-------------------------------------------------------------------------------------------
// Virtual destructors in C++. A virtual destructor ensures that the derived class's destructor
// is called when an object is deleted through a base class pointer.
// This is important for proper resource management and avoiding memory leaks.

class Base // Base class with a virtual destructor

{

	public:
		virtual ~Base() = default;


};

class Derived : public Base // Derived class inherits from Base class
{

	public:
		~Derived() override = default; // Override the base class destructor to ensure proper cleanup of derived class resources.
		

};

class AnotherDerived : public Base // Another derived class inherits from Base class
{
public:
	~AnotherDerived() override = default; // Override the base class destructor to ensure proper cleanup of another derived class resources.

};

int main() 
{
	// Implicit and explicit type conversion in C++. int to char and char to int, float to int, and int to float, etc.
	//----------------------------------------------------------------------------------------------------------------

	unsigned char a = 'a';
	int c = a; // 65; // Implicit conversion from unsigned char to int.

	std::cout << "a: " << c << std::endl; // Output: a: 97 from binary representation of 'a' in ASCII table.

	c = static_cast <unsigned char>(a); // Explicit conversion from unsigned char to int.

	std::cout << "c: " << c << std::endl; // Output: c: 97 from binary representation of 'a' in ASCII table.


	float f = 3.14f;
	double d = f; // Implicit conversion from float to double.

	f = static_cast <float>(d);
	std::cout << "d: " << d << std::endl; // Output: d: 3.14 from binary representation of 3.14 in double precision.
	


	f = static_cast <float>(d); 
	d = static_cast <double>(c); // Explicit conversion from int to double.
	c = static_cast <unsigned char>(d); // Explicit conversion from double to unsigned char.

	std::cout << "f: " << f << std::endl; // Output: f: 3.14 from binary representation of 3.14 in float precision.
	std::cout << "d: " << d << std::endl; // Output: d: 97 from binary representation of 97 in double precision.
	std::cout << "c: " << c << std::endl; // Output: c: 97 from binary representation of 97 in unsigned char precision.
	std::cout << "a: " << a << std::endl; // Output: a: 97 from binary representation of 97 in unsigned char precision.


	const float cf = 3.14159f;
	float* pf = const_cast <float*>(&cf); // Explicit conversion from const float* to float*.
	*pf = 2.0f; // Modifying the value of cf through pf.
	std::cout << "cf: " << cf << std::endl; // Output: cf: 2.0 from binary representation of 2.0 in float precision.
	std::cout << "sizeof(cf): " << sizeof(&cf) << std::endl; // Output: sizeof(cf): 8 from binary representation of 8 in size_t precision.


	// Dynamic casting in C++. dynamic_cast is used for safe downcasting in polymorphic class hierarchies.

	Base* basePtr = new Derived(); // Creating a Derived object and assigning it to a Base pointer.
	Derived* derivedPtr = dynamic_cast <Derived*>(basePtr); // Downcasting Base pointer to Derived pointer using dynamic_cast.
	AnotherDerived* anotherDerivedPtr = dynamic_cast <AnotherDerived*>(basePtr); // Downcasting Base pointer to AnotherDerived pointer using dynamic_cast.

	if (derivedPtr) {
		std::cout << "Successfully casted to Derived." << std::endl;
	}
	else {
		std::cout << "Failed to cast to Derived." << std::endl;
	}

	if (anotherDerivedPtr) {
		std::cout << "Successfully casted to AnotherDerived." << std::endl;
	}
	else {
		std::cout << "Failed to cast to AnotherDerived." << std::endl;
	}


	if (derivedPtr != nullptr)
	{
		std::cout << "Derived pointer is not null." << std::endl;
	}
	else
	{
		std::cout << "Derived pointer is null." << std::endl;
	}
	

	return 0;



}