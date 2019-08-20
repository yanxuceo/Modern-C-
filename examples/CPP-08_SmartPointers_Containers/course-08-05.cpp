#include <iostream>
#include <fstream>
#include <vector>


int main()
{
	std::string file_name = "image.dat";
	int r = 0, c = 0;

	std::ifstream in(file_name, std::ios_base::in | std::ios_base::binary);

	if(!in) {
		return EXIT_FAILURE;
	}

	in.read(reinterpret_cast<char*>(&r), sizeof(r));
	in.read(reinterpret_cast<char*>(&c), sizeof(c));
	std::cout << "Dim: " << r << " x " << c << std::endl;

	std::vector<float> data(r*c, 0);
	in.read(reinterpret_cast<char*>(&data.front()), data.size() * sizeof(data.front()));

	for(float d : data) {
		std::cout << d << std::endl;
	}

	return 0;
}