#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#include "caches.h"

#include <iostream>

void fully_associative_lru(std::ofstream& out_file, std::string file_name) {
	std::ifstream infile(file_name);
	std::string op;
	unsigned long long addr;
	int hits = 0;
	int accesses = 0;;
	int cache_size = 16384;
	std::vector<unsigned long long> cache;
	cache.resize(16384/32);
	std::vector<int> lru_queue;
	lru_queue.resize(16384/32);
	int offset_bits = log2(32);
	unsigned long long tag;
	int lru_way;
	int lru_queue_index;
	for (int i = 0; i < lru_queue.size(); i++) {
		lru_queue[i] = lru_queue.size() - i - 1;
	}
	//std::cout << cache.size();
	
	while (infile >> op >> std::hex >> addr) {
		tag = addr >> offset_bits;
		bool found = false;
		for (int i = 0; i < cache.size(); i++) {
			if (tag == cache[i]) { //if there is a cache hit 
				hits++; //increase hit counter
				for (lru_queue_index = 0; lru_queue_index < lru_queue.size(); lru_queue_index++) { //search lru_queue for set way used in cache, preserve set way index
					if (lru_queue[lru_queue_index] == i) { //if set way is found
						lru_way = lru_queue[lru_queue_index]; //set lru_way equal to the 
						break;
					}
				}
				lru_queue.erase(lru_queue.begin() + lru_queue_index); //removed accessed set way from lru_queue
				lru_queue.insert(lru_queue.begin(), lru_way); //insert set way back at the begining of the lru_queue
				found = true; //set found flag true
				break; //exit the loop
			}
		}
		if (!found) { //if found flag remains false
			lru_way = lru_queue[lru_queue.size() - 1]; //get last element from lru_queue (lru element)
			cache[lru_way] = tag; //set cache at lru_way with new memory address tag
			lru_queue.pop_back(); //pop set way from lru_queue
			lru_queue.insert(lru_queue.begin(), lru_way); //insert removed set way back to lru_queue
		}
		accesses++;
	}
	out_file << hits << "," << accesses << ";";
	infile.close();
}