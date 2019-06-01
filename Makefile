#CXX=g++-9
BIN_DIR := ./bin
SRC_DIR := ./src
OBJ_DIR := ./build

UT_DIR := $(SRC_DIR)/ut
APP_INC := -I $(SRC_DIR)
UT_INC := -I $(UT_DIR)

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
UT_FILES := $(wildcard $(UT_DIR)/*.cpp)

MAIN_OBJ := $(OBJ_DIR)/main.o
O_FILES := $(filter-out $(MAIN_OBJ),$(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.cpp=.o))))
UT_O_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(UT_FILES:.cpp=.o)))
CXXFLAGS ?= -Wall -Wextra -Werror -std=c++17 $(APP_INC)

####

ut: $(O_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) -c -o build/ut.o $(UT_DIR)/ut.cpp $(CXXFLAGS) $(UTFLAGS)
	$(CXX) -o bin/$@ $(filter-out build/main.o,$^) build/ut.o $(CXXFLAGS)

lox: $(O_FILES) $(MAIN_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o bin/$@ $^ $(CXXFLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(OBJ_DIR)
	$(CXX) -c -o $@ $(SRC_DIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)

.PHONY: cleanall clean debug
clean:
	$(RM) -r build

cleanall: clean
	$(RM) -r bin

debug:
	@echo $(SRC_FILES)
	@echo $(O_FILES)
	@echo $(UT_O_FILES)

