#include <iostream>
#include <fstream>

#include "direct-mapped.h"
#include "set_associative.h"

int main(int argc, char* argv[]) {
	if(argc != 3){
		std::cout << "usage: ./cache-sim [INPUT FILE] [OUTPUT FILE]" << std::endl;
		return 0;
	}
	std::ofstream out_file(argv[2]);
	direct_mapped(out_file, argv[1]);
	set_associative(out_file, argv[1]);
}