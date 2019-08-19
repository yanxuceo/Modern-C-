#include <iostream>
#include <vector>

class Strategy {
public:
    virtual void Print() const = 0;    
};

class Strategy_A : public Strategy {
public:
    void Print() const override { std::cout << "A" << std::endl; }    
};

class Strategy_B : public Strategy {
public:
    void Print() const override {std::cout << "B" << std::endl; }    
};

class MyStruct {
public:
    MyStruct(const Strategy& s)
        :strategy_(s)
    {}

    void Print() const {strategy_.Print();};

private:
    const Strategy& strategy_;    
};

int main() {
    Strategy_A a;
    MyStruct struct_a(a);
    struct_a.Print();

    Strategy_B b;
    MyStruct struct_b(b);
    struct_b.Print();

    return 0;
}
