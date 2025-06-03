CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++23 -I. -O3
LDFLAGS := -pthread -lstdc++fs 

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
EXECUTABLE := $(BIN_DIR)/game

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

.PHONY: all clean run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS) $(CXXFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	@echo "Запуск программы..."
	@./$(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
