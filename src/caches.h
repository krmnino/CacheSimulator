#ifndef CACHES
#define CACHES

#include <string>

void direct_mapped(std::ofstream&, std::string);
void set_associative(std::ofstream&, std::string);
void fully_associative_lru(std::ofstream&, std::string);
void fully_associative_hc(std::ofstream&, std::string);
void set_associative_ns(std::ofstream&, std::string);
void set_associative_prefetch(std::ofstream&, std::string);
void set_associative_prefetch_miss(std::ofstream&, std::string);

#endif
