#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#include "caches.h"

#include <iostream>

void fully_associative_hc(std::ofstream& out_file, std::string file_name) {
	std::ifstream infile(file_name);
	std::string op;
	unsigned long long addr;
	int hits;
	int accesses;
	int cache_size = 16384;
	std::vector<unsigned long long> cache;
	cache.resize(16384 / 32);
	//std::cout << cache.size();
	while (infile >> op >> std::hex >> addr) {

	}
}