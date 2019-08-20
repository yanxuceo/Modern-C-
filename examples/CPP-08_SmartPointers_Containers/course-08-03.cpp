#include <string>
#include <iostream>
#include <memory>
#include <vector>

class AbstractShape {
public:
	virtual void Print() const = 0;	
};

class Square : public AbstractShape {
public:
	void Print() const override {std::cout << "Square\n";}
};

class Triangle : public AbstractShape {
public:
	void Print() const override {std::cout << "Triangle\n";}	
};


int main()
{
	std::vector<std::unique_ptr<AbstractShape>> shapes;
	shapes.emplace_back(new Square);

	auto triangle = std::unique_ptr<Triangle>(new Triangle);
	shapes.emplace_back(std::move(triangle));

	shapes.emplace_back(std::make_unique<Triangle>());

	for(const auto& shape : shapes)
	{
		shape->Print();
	}

	return 0;
}