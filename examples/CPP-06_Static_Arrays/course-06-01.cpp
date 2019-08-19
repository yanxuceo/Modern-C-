#include <iostream>
#include <vector>

class Counted {
public:
    Counted() {Counted::count++;}    
    ~Counted() {Counted::count--;}

    static int count;
};

int Counted::count = 0;  // definition

int main() {
    Counted a, b;
    std::cout << "Count: " << Counted::count << std::endl;

    Counted c;
    std::cout << "Count: " << Counted::count << std::endl;    

    return 0;
}
