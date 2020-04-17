#ifndef DM
#define DM

#include <fstream>
#include <string>
#include <vector>
#include <math.h>

void direct_mapped(std::ofstream &out_file, std::string file_name){
    std::string op;
	unsigned long long addr;
	int hits;
	int accesses;
	int extractor;
	int offset_bits;
	int set_index_bits;
	int cache_size;
	int set_index;
	unsigned long long tag;
	int sizes[] = {1024, 4096, 16384, 32768}; //cache sizes: 1KB, 4KB, 16KB, 32KB
    for(int i = 0; i < int(sizeof(sizes)/sizeof(sizes[0])); i++){
		std::ifstream infile(file_name);
		accesses = 0;
		hits = 0;
		cache_size = sizes[i]/32;
		std::vector<long long> cache;
		cache.resize(cache_size);
		set_index_bits = 5;
		switch(cache_size){
			case 32:
				extractor = 0x1F;
				set_index_bits = 5;
				break;
			case 128:
				extractor = 0x7F;
				set_index_bits = 7;
				break;
			case 512:
				extractor = 0x1FF;
				set_index_bits = 9;
				break;
			case 1024:
				extractor = 0x3FF;
				set_index_bits = 10;
				break;
			default:
				break;
		}
		while (infile >> op >> std::hex >> addr) {
			offset_bits = log2(32); //lg(cache_size) and cache_size = 32 bytes
			addr = addr >> offset_bits;  //shift right address 5 bits
			set_index = addr & extractor; //extract set index using corresponding extractor
			tag = addr >> set_index_bits; //shift right address number of bits of set_index
			if(tag == cache[set_index]){ //if tag == cache, then cache hit
				hits++;
			}
			else{ //else, cache miss and update cache entry
				cache[set_index] = tag;
			}
			accesses++;
		}
		out_file << hits << "," << accesses << ";";
		if(i != int(sizeof(sizes)/sizeof(sizes[0])) - 1){
			out_file << " ";
		}
		infile.close();
	}
}

#endif