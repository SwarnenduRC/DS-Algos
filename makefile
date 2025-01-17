##Directories
SRC_DIR := src
SRC_TEST_DIR := $(SRC_DIR)/test
INC_DIR := include
INC_TEST_DIR := $(INC_DIR)/test
OBJ_DIR := obj
BIN_DIR := bin

##Compiler flags
CXX := clang++

CXXFLAGS := -std=c++20 -g -Wall -Wextra -Werror -Wno-unused-function \
			-I$(INC_DIR) -I$(INC_TEST_DIR) \
			$(addprefix -I, $(wildcard $(INC_DIR)/*), $(wildcard $(INC_TEST_DIR)/*))

##Files
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
#SRCS := $(wildcard *.cpp $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DBG_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%_d.o, $(SRCS))

##Binaries
TARGET := $(BIN_DIR)/DS-Algos
DBG_TARGET := $(BIN_DIR)/DS-AlgosD

all : debug release

release : $(TARGET)

debug : $(DBG_TARGET)


$(TARGET) : $(OBJS) | $(BIN_DIR)
	@echo "Linking release build...."
	$(CXX) $(CXXFLAGS) -lgtest -lgmock -lpthread -o $@ $^
	@echo "Linking release build completed"

$(DBG_TARGET) : $(DBG_OBJS) | $(BIN_DIR)
	@echo "Linking debug build...."
	$(CXX) $(CXXFLAGS) -lgtest -lgmock -lpthread -o $@ $^
	@echo "Linking debug build completed"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling release build...."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiling release build completed"

$(OBJ_DIR)/%_d.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling debug build...."
	$(CXX) $(CXXFLAGS) -c $< -o $@ -DDEBUG
	@echo "Compiling debug build completed"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/test

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	@echo "Cleaning solution..."
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TARGET) $(DBG_TARGET)
	@echo "Cleaning solution completed"

.PHONY: all release debug clean
