#include <iostream>
#include <fstream>

#include "direct-mapped.cpp"

int main(int argc, char* argv[]) {
	if(argc != 3){
		std::cout << "usage: ./cache-sim [INPUT FILE] [OUTPUT FILE]" << std::endl;
		return 0;
	}
	std::ofstream out_file(argv[2]);
	direct_mapped(out_file, argv[1]);
}