CXXFLAGS = -std=c++17

DEPS =	direct-mapped.cpp set_associative.cpp set_associative_ns.cpp set_associative_prefetch.cpp\
		set_associative_prefetch_miss.cpp fully_associative_hc.cpp fully_associative_lru.cpp

OBJS =	direct-mapped.o set_associative.o set_associative_ns.o set_associative_prefetch.o\
		set_associative_prefetch_miss.o fully_associative_hc.o fully_associative_lru.o

cache-sim: cache-sim.o $(OBJS)
	g++ cache-sim.o $(OBJS) -o cache-sim

cache-sim.o: cache-sim.cpp 
	g++ -c $(CXXFLAGS) cache-sim.cpp

$(OBJS): $(DEPS)
	g++ -c $(CXXFLAGS) $(DEPS)

clean:
	rm *.o cache-sim