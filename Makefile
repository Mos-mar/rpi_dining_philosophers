CC =gcc
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -Iinclude -pthread
LDFLAGS = -pthread -lgpiodcxx -lgpiod

SRC_DIR = src
OBJ_DIR = obj
BIN = diningPhilosophers

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN)
