#include <iostream>
#include <fstream>

/*
#include "direct-mapped.cpp"
#include "set_associative.cpp"
#include "fully_associative_lru.cpp"
#include "fully_associative_hc.cpp"
#include "set_associative_ns.cpp"
#include "set_associative_prefetch.cpp"
#include "set_associative_prefetch_miss.cpp"
*/

#include "caches.h"

int main(int argc, char* argv[]) {
	if(argc != 3){
		std::cout << "usage: ./cache-sim [INPUT FILE] [OUTPUT FILE]" << std::endl;
		return 0;
	}
	std::ofstream out_file(argv[2]);
	direct_mapped(out_file, argv[1]);
	set_associative(out_file, argv[1]);
	fully_associative_lru(out_file, argv[1]);
	fully_associative_hc(out_file, argv[1]);
	set_associative_ns(out_file, argv[1]);
	set_associative_prefetch(out_file, argv[1]);
	set_associative_prefetch_miss(out_file, argv[1]);
	out_file.close();
}