#include <vector>
#include <iostream>
#include <algorithm>

class Human {
public:
    Human(int kindness) 
        : kindness_(kindness)
    {

    }   

    bool operator<(const Human& other) const {
        return kindness_ < other.kindness_;
    } 

    int getKindness() const 
    {
        return kindness_;
    }

private:
    int kindness_ = 100;
};


int main() {
    std::vector<Human> humans{Human(3), Human(0), Human(10)};
    std::sort(humans.begin(), humans.end());

    std::cout << humans.at(0).getKindness() << std::endl;
    std::cout << humans.at(1).getKindness() << std::endl;

    return 0;
}