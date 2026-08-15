#include <iostream>
#include <memory>

class widget
{
public: 
	explicit widget(int data) : data_(data) {} // explicit constructor to prevent implicit conversions

	void do_something() // member function that does something with the widget
	{
		std::cout << "widget is doing something with value " << data_ << std::endl; 
	}

	int get_data() const { return data_; } // getter function to access the private data member

private:
	int data_;
};

int main()
{
	// use a shared_ptr to manage the widget
	std::shared_ptr<widget> w = std::make_shared<widget>(42); // create a shared_ptr to a widget with data 42
	w->do_something();

	// access data via getter
	std::cout << w->get_data() << std::endl;
























	return 0;
}
