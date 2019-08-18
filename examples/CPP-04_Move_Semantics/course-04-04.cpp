#include <iostream>

class Hmm {
public:
    Hmm() {std::cout << "default" << std::endl;}
    Hmm(const Hmm& other) {std::cout << "copy constructor" << std::endl;}
    Hmm(Hmm&& other) {std::cout << "move constructor" << std::endl;}
    
    Hmm& operator=(const Hmm& other) {
        std::cout << "copy assignment operator" << std::endl;
        return *this;
    }

    Hmm& operator=(Hmm&& other) {
        std::cout << "move assignment operator" << std::endl;
        return *this;
    }
};

int main()
{
    Hmm a;
    Hmm b = a;
    a = b;
    Hmm c = std::move(a);
    c = std::move(b);

    return 0;
}