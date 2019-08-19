#include <iostream>
#include <vector>

class Printable {
public:
    virtual void Print() const = 0; 
};

class Rect : public Printable {
public:
    Rect(int w, int h)
         : width_(w), height_(h) {

    }

    virtual void Print() const {
        std::cout << "rect: " << width_ << " " << height_ << std::endl;
    }
    
    int width() const { return width_; }
    int height() const { return height_; }

protected:
    int width_ = 0;
    int height_ = 0;
};

class Square : public Rect {
public:
    explicit Square(int size) 
        : Rect(size, size)
    {}

    virtual void Print() const override{
        std::cout << "square: " << width_ << " " << height_ << std::endl;
    }
};

int main() {
    Square square(10);
    //Square square = 'a';

    const Rect& rect_ref = square;
    rect_ref.Print();

    return 0;
}
