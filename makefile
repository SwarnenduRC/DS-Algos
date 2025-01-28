##Directories
SRC_DIR := src
TEST_DIR := test
INC_DIR := include
OBJ_DIR := obj
TEST_OBJ_DIR := obj/test
BIN_DIR := bin

##Compiler flags
CXX := clang++

CXXFLAGS := -std=c++20 -g -Wall -Wextra -Werror -Wno-unused-function \
			-I$(INC_DIR) -I$(TEST_DIR) \
			$(addprefix -I, $(wildcard $(INC_DIR)/*), $(wildcard $(TEST_DIR)/*))

##Files
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
TEST_SRCS := $(shell find $(TEST_DIR) -name "*.cpp")
MAIN_SRC := $(wildcard *.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS) $(MAIN_SRC))
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/test/%.o, $(TEST_SRCS))
DBG_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%_d.o, $(SRCS) $(MAIN_SRC))
DBG_TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/test/%_d.o, $(TEST_SRCS))

##Binaries
TARGET := $(BIN_DIR)/DS-Algos
DBG_TARGET := $(BIN_DIR)/DS-AlgosD

all : debug release

release : $(TARGET)

debug : $(DBG_TARGET)


$(TARGET) : $(OBJS) $(TEST_OBJS) | $(BIN_DIR)
	@echo "Linking release build...."
	$(CXX) $(CXXFLAGS) -lgtest -lgmock -lpthread -o $@ $^
	@echo "Linking release build completed"

$(DBG_TARGET) : $(DBG_OBJS) $(DBG_TEST_OBJS) | $(BIN_DIR)
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

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(TEST_OBJ_DIR)
	@echo "Compiling test release build...."
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiling release build completed"

$(TEST_OBJ_DIR)/%_d.o: $(TEST_DIR)/%.cpp | $(TEST_OBJ_DIR)
	@echo "Compiling debug test build...."
	$(CXX) $(CXXFLAGS) -c $< -o $@ -DDEBUG
	@echo "Compiling debug build completed"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/test

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	@echo "Cleaning solution..."
	rm -rf $(OBJ_DIR) $(TEST_OBJ_DIR) $(BIN_DIR) $(TARGET) $(DBG_TARGET)
	@echo "Cleaning solution completed"

.PHONY: all release debug clean
