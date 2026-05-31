СXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

TARGET = sudoku_game

SRCS = src/main.cpp src/SudokuModel.cpp src/SudokuView.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

