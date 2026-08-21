#include <iostream>

template <typename T>
decltype(auto)	 max(const T* a, const T* b) {
	if (!a || !b) return *a; // simple null check, return first if second is null.
	return (*a > *b) ? *a : *b;

	void swap(T & a, T & b);

		T tmp = *a;
		a = b;


		std::cout << "a = " << a << std::endl; // a.
		std::cout << "b = " << b << std::endl; // b.
}

int main() {		
	

	int a = 5;
	int b = 10;

	int c = max(&a, &b);

	std::cout << "c = " << c << std::endl; // print the results..

	return 0;
}
