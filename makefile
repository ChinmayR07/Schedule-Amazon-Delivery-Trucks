# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Project files
SOURCES = main.cpp Schedule.cpp Route.cpp DeliveryRequest.cpp AddressList.cpp
HEADERS = Schedule.h Route.h Address.h DeliveryRequest.h AddressList.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = program

# Build rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generic rule for object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean