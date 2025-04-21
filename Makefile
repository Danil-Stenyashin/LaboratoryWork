CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
GTEST_LIBS = -lgtest -lgtest_main -pthread

SRC = VisualNovel.cpp Character.cpp Player.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = VisualNovel

TEST_SRC = test.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_DEPS = Character.o Player.o
TEST_EXEC = runTests

.PHONY: all clean run test tests

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

tests: $(TEST_OBJ) $(TEST_DEPS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $^ $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(EXEC) $(TEST_EXEC)

run: all
	./$(EXEC)

test: tests
	./$(TEST_EXEC)

