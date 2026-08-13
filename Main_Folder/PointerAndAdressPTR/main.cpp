#include <iostream>




int main()

{
	// & is the address-of operator, which returns the memory address of a variable.
	// * is the dereference operator, which returns the value stored at a given memory address.
	//-------------------------------------------------------------------------------------------//

	int a = 5;
	int b = 6;
	int c = 7;
	const char* name = "Simon";
	int* pi = &a; // pointer to int (store the address of "a" in "pi")
	int* pj = &b; // pointer to int (store the address of "b" in "pj")
	int* pk = &c; // pointer to int (store the address of "c" in "pk")


	// Print out the values of a, b, and name
	std::cout << "Hello, " << name << "!" << std::endl;
	std::cout << "The value of a is: " << a << std::endl;
	std::cout << "The value of b is: " << b << std::endl;
	std::cout << "The value of c is: " << c << std::endl;
	std::cout << "The address of pi is: " << pi << std::endl;
	std::cout << "The original address of a is: " << &a << std::endl;
	std::cout << "The value pointed to by pi is: " << *pi << std::endl;

	// Now let's do the same for b and pj
	std::cout << "The address of pj is: " << pj << std::endl;
	std::cout << "The original address of b is: " << &b << std::endl;
	std::cout << "The value pointed to by pj is: " << *pj << std::endl;

	// dereference the pointers to get the values of a, b, and c, then add them together
	std::cout << "The value added together is: " << *pj + *pi + *pk << std::endl; 
	

	// Now let's change the values of a and b through the pointers pi and pj
	std::cout << "value of a is: " << a << std::endl;
	std::cout << "value of b is: " << b << std::endl;
	std::cout << "value of c is: " << c << std::endl;
	*pi = 10; // change the value of a through the pointer pi
	*pj = 15; // change the value of b through the pointer pj
	*pk = 20; // change the value of c through the pointer pk


	// Print out the new values of a, b, and c
	std::cout << "The new value of a is: " << a << std::endl;
	std::cout << "The new value of b is: " << b << std::endl;
	std::cout << "The new value of c is: " << c << std::endl;
	std::cout << "The original address of a is: " << &a << std::endl;
	std::cout << "The original address of b is: " << &b << std::endl;
	std::cout << "The original address of c is: " << &c << std::endl;

	if(*pi == a)
	{
		std::cout << "The value of a is equal to the value pointed to by pi." << std::endl;
	}
	else
	{
		std::cout << "The value of a is not equal to the value pointed to by pi." << std::endl;
	}

	// Now let's print out the letters of the name "Simon" using pointer arithmetic
	std::cout << "The first letter of the name is in Simon: " << name[0] << std::endl;
	std::cout << "The second letter of the name is in Simon: " << name[1] << std::endl;
	std::cout << "The third letter of the name is in Simon: " << name[2] << std::endl;


	int& ref_a = a; // reference to a = 10 which take the value of a and store it in ref_a new value from *pi = 10
	std::cout << "The value of a is: " << a << std::endl;
	





	return 0;
}

	