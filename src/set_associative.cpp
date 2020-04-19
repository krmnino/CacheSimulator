#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#include "set_associative.h"

#include <iostream>

void set_associative(std::ofstream &out_file, std::string file_name){
    std::string op;
	unsigned long long addr;
	int hits;
	int accesses;
    int cache_size = 16384; //16KB, 32 bytes per line = 512 cache lines
	int offset_bits;
	int extractor;
	int set_index;
	int set_index_bits;
	unsigned long long tag;
    for(int i = 2; i < 17; i *= 2){ //associativity of 2, 4, 8, 16
        std::ifstream infile(file_name);
		accesses = 0;
		hits = 0;
        std::vector<std::vector<unsigned long long>> cache; //cache with cache_size/32/i # of sets and i # of ways
        cache.resize(cache_size/32/i, std::vector<unsigned long long>(i));
        std::vector<std::vector<int>> lru_queue; //keeps track of the cache lines per set, most recently used closer to index 0
        lru_queue.resize(cache_size/32/i, std::vector<int>(i));
		int lru_way;
		int lru_queue_index;
		for (int j = 0; j < lru_queue.size(); j++) {
			for (int k = 0; k < lru_queue[i].size(); k++) {
				lru_queue[j][k] = lru_queue[j].size() - k - 1;
			}
		}
		offset_bits = log2(32);
		switch (cache_size/32/i) {
		case 32:
			extractor = 0x1F;
			set_index_bits = 5;
			break;
		case 64:
			extractor = 0x3F;
			set_index_bits = 6;
			break;
		case 128:
			extractor = 0x7F;
			set_index_bits = 7;
			break;
		case 256:
			extractor = 0xFF;
			set_index_bits = 8;
			break;
		default:
			break;
		}
		while (infile >> op >> std::hex >> addr) {
			addr = addr >> offset_bits;
			set_index = addr & extractor;
			tag = addr >> set_index_bits;
			bool found = false;
			for (int j = 0; j < cache[set_index].size(); j++) {
				if (tag == cache[set_index][j]) {
					hits++;
					for (lru_queue_index = 0; lru_queue_index < lru_queue[set_index].size(); lru_queue_index++) {
						if (lru_queue[set_index][lru_queue_index] == j) {
							lru_way = lru_queue[set_index][lru_queue_index];
							break;
						}
					}
					lru_queue[set_index].erase(lru_queue[set_index].begin() + lru_queue_index);
					lru_queue[set_index].insert(lru_queue[set_index].begin(), lru_way);
					found = true;
					break;
				}
			}
			if (!found) {
				lru_way = lru_queue[set_index][lru_queue[set_index].size() - 1];
				cache[set_index][lru_way] = tag;
				lru_queue[set_index].pop_back();
				lru_queue[set_index].insert(lru_queue[set_index].begin(), lru_way);
			}
			accesses++;
		}
		out_file << hits << "," << accesses << ";";
		if (i != 16) {
			out_file << " ";
		}
		infile.close();
    }
}