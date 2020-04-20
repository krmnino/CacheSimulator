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
	int hits = 0;
	int accesses = 0;
	int total_cache_size = 16384;
	int offset_bits = log2(32);
	std::vector<unsigned long long> cache;
	cache.resize(total_cache_size / 32); //resize cache to 512 entries
	std::vector<int> bin_tree_hc; //binary tree (array representation) to track the least recently used cache line
	bin_tree_hc.resize(total_cache_size / 32 - 1, 0); //need 2 * cache lines + 1 entries to represent the binary tree in a vector
	int bin_tree_index;
	unsigned long long tag;
	while (infile >> op >> std::hex >> addr) {
		tag = addr >> offset_bits;
		bool found = false;
		int cache_index;
		for (cache_index = 0; cache_index < cache.size(); cache_index++) {
			if (tag == cache[cache_index]) { //if there is a cache hit 
				hits++; //increase hit counter
				bin_tree_index = cache_index + bin_tree_hc.size() - 1;
				while (bin_tree_index != 0) {
					if (bin_tree_index % 2 == 0) {
						bin_tree_index = (bin_tree_index - 2) / 2;
						bin_tree_hc[bin_tree_index] = 0;
					}
					else {
						bin_tree_index = (bin_tree_index - 1) / 2;
						bin_tree_hc[bin_tree_index] = 1;
					}
				}
				found = true;
				break;
			}
		}
		if (!found) {
			bin_tree_index = 0;
			int curr_level = 0;
			while (curr_level < log2(cache.size())) {
				if (bin_tree_hc[bin_tree_index] == 0) {
					bin_tree_hc[bin_tree_index] = 1;
					bin_tree_index = 2 * bin_tree_index + 1;
					curr_level++;
				}
				else {
					bin_tree_hc[bin_tree_index] = 0;
					bin_tree_index = 2 * bin_tree_index + 2;
					curr_level++;
				}
			}
			bin_tree_index = bin_tree_index - cache.size() + 1;
			cache[bin_tree_index] = tag;
		}
		accesses++;
	}
	out_file << hits << "," << accesses << ";" << std::endl;
}