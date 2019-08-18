#include <iostream>
#include <string>


class Printer {
public:
    void Print(const std::string& str) {
        std::cout << "lvalue: " << str << std::endl;
    }

    void Print(std::string&& str) {
        std::cout << "rvalue: " << str << std::endl;
        some_str = str;
    }

private:
    std::string some_str;
};


int main() {
    std::string hello = "Hi";
    Printer printer;
    
    printer.Print(hello);
    printer.Print("world");
    printer.Print(std::move(hello));
    // DO NOT access "hello" after move!

    std::cout << hello << std::endl;

    return 0;
}