CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
GTEST_LIBS = -lgtest -lgtest_main -pthread

SRC = VisualNovel.cpp Character.cpp Player.cpp
TEST_SRC = test.cpp
OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o) Character.o Player.o  # Добавляем Character и Player в тесты
EXEC = VisualNovel
TEST_EXEC = runTests

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

tests: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_OBJ) $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(EXEC) $(TEST_EXEC)

run: all
	./$(EXEC)

test: tests
	./$(TEST_EXEC)

