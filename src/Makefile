TARGET = cache-sim

OBJS = cache-sim.o\

CXX = g++
CXXFLAGS = -std=c++17

$(TARGET):	$(OBJS)	
		$(CXX) $(CXXFLAGS) cache-sim.o -g -o $(TARGET)

clean:
		rm -f *.o $(TARGET)

cache-sim.o: 	cache-sim.cpp