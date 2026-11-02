CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC = src/bet.cpp src/player.cpp src/table.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = casino_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) run_tests

test:
	$(CXX) $(CXXFLAGS) tests/table_test.cpp src/bet.cpp src/player.cpp src/table.cpp -lgtest -lgtest_main -pthread -o run_tests
	./run_tests
	rm -f run_tests