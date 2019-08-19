#include <iostream>

int main() {
    float k = 3.14159;
    std::cout << "sizeof("<< k <<") is " << sizeof(k)
              << " bytes or " << sizeof(k) * 8 << " bits." 
              << std::endl;

    return 0;
}
