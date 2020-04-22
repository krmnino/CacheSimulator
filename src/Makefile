TARGET = cache-sim

OBJS = 	cache-sim.o 

CXX = g++
CXXFLAGS = -std=c++17

$(TARGET):	$(OBJS)	
		$(CXX) $(CXXFLAGS) $(OBJS) -g -o $(TARGET)

clean:
		rm -f *.o $(TARGET)

cache-sim.o: 	cache-sim.cpp