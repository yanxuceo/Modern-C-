#include <iostream>

int main() {
    unsigned short int k = 37;
    std::cout << "sizeof("<< k <<") is " << sizeof(k)
              << " bytes or " << sizeof(k) * 8 << " bits." 
              << std::endl;

    return 0;
}
