#ifndef SA
#define SA

#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#include <iostream>

void set_associative(std::ofstream &out_file, std::string file_name){
    std::string op;
	unsigned long long addr;
	int hits;
	int accesses;
    int cache_size = 16384; //16KB, 32 bytes per line = 512 cache lines
    for(int i = 2; i < 17; i *= 2){ //associativity of 2, 4, 8, 16
        std::ifstream infile(file_name);
		accesses = 0;
		hits = 0;
        std::vector<std::vector<unsigned long long>> cache;
        cache.resize(cache_size/32/i, std::vector<unsigned long long>(i));
        std::vector<int> lru_queue; //keeps track of the cache lines per set, most recently used closer to index 0
        lru_queue.resize(cache_size/32/i, -1);
        //std::cout << cache.size() << " sets *" << cache[0].size() << "ways" << std::endl;
    }
}

#endif