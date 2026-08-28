#include <iostream>
#include <algorithm>
#include <utility>
#include <cstddef>
                  



// semantics //
 // steal ressources to another one instead of delete it.
class Buffer {
private:
    int* data;
    std::size_t size;

public:
    Buffer() : data(nullptr), size(0) {}
    Buffer(std::size_t s) : data(new int[s]()), size(s) {}
    ~Buffer() { delete[] data; }


    // Copy constructor
    Buffer(const Buffer& other) : data(other.size ? new int[other.size] : nullptr), size(other.size) {
        if (data) std::copy(other.data, other.data + other.size, data);
        std::cout << "Buffer copied to b (size=" << size << ")\n";
    }

    // Move constructor
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Buffer moved (size=" << size << ")\n";
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this;
        int* newData = other.size ? new int[other.size] : nullptr;
        if (newData) std::copy(other.data, other.data + other.size, newData);
        delete[] data;
        data = newData;
        size = other.size;
        std::cout << " A ....Buffer copy-assigned (size=" << size << ")\n";
        return *this;
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        std::cout << "Buffer move-assigned b to a(0) : (size=" << size << ")\n"; // a become 0 pass to b.
        return *this;
    }

    void set(std::size_t idx, int value) {
        if (idx < size) data[idx] = value;
    }

    void print() const {
        std::cout << "Buffer(size=" << size << "): ";
        for (std::size_t i = 0; i < size; ++i) std::cout << data[i] << (i + 1 < size ? ", " : "\n");
    }
};

int main() {


    std::cout << "Semantics copy, steal and move numbers, buffer memory " << std::endl;
    std::cout << "--------------------------------------- " << std::endl;

    // Create a buffer and populate it
    Buffer a(0b11011);
    for (std::size_t i = 0; i < 5; ++i) a.set(i, static_cast<int>(i + 1));
    a.print();

    // Copy construction (deep copy)
    Buffer b = a;
    b.print();

    // Move construction (steal resources)
    Buffer c = std::move(a);
    c.print();
    a.print(); // a is now empty (size 0)

    // Move assignment from a temporary
    b = Buffer(0b01011);
    for (std::size_t i = 0; i < 3; ++i) b.set(i, static_cast<int>((i + 1) * 10));
    b.print();

    // Copy assignment
    c = b;
    c.print();

    return 0;
}
