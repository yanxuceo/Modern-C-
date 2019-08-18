#include <iostream>

class Blah {
public:
    void SomeFunc() const {std::cout << "const" << std::endl;}
    void SomeFunc() {std::cout << "non const" << std::endl;};
};

int main() {
    Blah blah;
    blah.SomeFunc();

    const Blah& blah_ref = blah;
    blah_ref.SomeFunc();

    return 0;
}