#include <iostream>
#include <memory>
#include <vector>

// A simple class to demonstrate smart pointers
class widget
{
public:
    // delete default and copy operations to avoid accidental copies
    widget() = delete;
    widget(const widget&) = delete;
    widget& operator=(const widget&) = delete;

    // allow move semantics
    widget(widget&&) noexcept = default;
    widget& operator=(widget&&) noexcept = default;

    // constructor allocates internal buffer
    explicit widget(std::size_t size) : size_(size), buffer_(std::make_unique<int[]>(size))
    {
        for (std::size_t i = 0; i < size_; ++i) buffer_[i] = static_cast<int>(i);
        std::cout << "widget constructed (size=" << size_ << ")\n";
    }
	//  destructor releases resources
    ~widget() { std::cout << "widget destroyed (size=" << size_ << ")\n"; }


	// member function to demonstrate functionality
    void do_something() const
    {
        std::cout << "widget is doing something; first element: " << (size_ ? buffer_[0] : -1) << std::endl;
    } 

    std::size_t size() const { return size_; }

private:
    std::size_t size_;
	std::unique_ptr<int[]> buffer_; // unique_ptr to manage dynamic array
};

int main()
{
    // unique_ptr: sole ownership
    auto u = std::make_unique<widget>(5);
    u->do_something();
    std::cout << "unique_ptr widget size: " << u->size() << std::endl;

    // shared_ptr: shared ownership
    auto s1 = std::make_shared<widget>(3);
    {
        std::shared_ptr<widget> s2 = s1; // increment reference count
        s2->do_something();
        std::cout << "shared_ptr use_count: " << s1.use_count() << std::endl;
    }
	// s2 goes out of scope, reference count decremented
    std::cout << "shared_ptr use_count after scope: " << s1.use_count() << std::endl;

    // weak_ptr: non-owning reference to shared_ptr-managed object
    std::weak_ptr<widget> wk = s1;
	if (auto locked = wk.lock()) { // lock weak_ptr to get shared_ptr
        std::cout << "weak_ptr locked; size: " << locked->size() << std::endl;
    } else {
        std::cout << "weak_ptr expired" << std::endl;
    }

    // reset shared_ptr to destroy the object
    s1.reset();
	if (wk.expired()) std::cout << "after reset: weak_ptr expired\n"; // Check if the weak_ptr has expired after resetting the shared_ptr
	else std::cout << "after reset: weak_ptr still valid\n";

    return 0;
}
