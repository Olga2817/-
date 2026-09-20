CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = homework2
HEADERS = complex.hpp algebraic.hpp trigonometric.hpp quad.hpp

all: $(TARGET)

$(TARGET): main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all	