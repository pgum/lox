SRC_DIR := ./src
OBJ_DIR := ./build

UT_SUF := $(SRC_DIR)/ut
APP_INC := -I $(SRC_DIR)
UT_INC := -I $(UT_SUF)

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
UT_FILES := $(wildcard $(UT_SUF)/*.cpp)

MAIN_OBJ := $(OBJ_DIR)/main.o
O_FILES := $(filter-out $(MAIN_OBJ),$(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.cpp=.o))))
UT_O_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(UT_FILES:.cpp=.o)))
CXXFLAGS ?= -Wall -Wextra -Werror -std=c++17 $(APP_INC)

.PHONY: clean

ut: $(O_FILES)
	$(CXX) -c -o $(OBJ_DIR)/ut.o $(UT_SUF)/ut.cpp $(CXXFLAGS) $(UTFLAGS)
	$(CXX) -o $@ $^ $(OBJ_DIR)/ut.o $(CXXFLAGS)

lox: $(O_FILES) $(MAIN_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) -r $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(OBJ_DIR)
	$(CXX) -c -o $@ $(SRC_DIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)
