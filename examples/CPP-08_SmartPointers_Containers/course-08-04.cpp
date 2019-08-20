#include <iostream>
#include <fstream>
#include <vector>


int main()
{
	std::string file_name = "image.dat";
	std::ofstream file(file_name, std::ios_base::out | std::ios_base::binary);

	if(!file) {
		return EXIT_FAILURE;
	}

	int r = 2;
	int c = 3;
	std::vector<float> vec(r*c, 42);
	file.write(reinterpret_cast<char*>(&r), sizeof(r));
	file.write(reinterpret_cast<char*>(&c), sizeof(c));

	std::cout << vec.front() << std::endl;
	std::cout << "The vector size is: "<< vec.size() << std::endl;
	std::cout << "The vector element size is: " << sizeof(vec.front()) << std::endl;

	file.write(reinterpret_cast<char*>(&vec.front()), vec.size()*sizeof(vec.front()));

	return 0;
}