SRC_DIR := src
OBJ_DIR := build
UTOBJ_DIR := buildut

UT_SUF := $(SRC_DIR)/ut
APP_INC := -I $(SRC_DIR)
UT_INC := -I $(UT_SUF)

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
UT_FILES := $(wildcard $(UT_SUF)/*_ut.cpp)

MAIN_OBJ := $(OBJ_DIR)/main.o
UTMAIN_OBJ := $(UTOBJ_DIR)/utmain.o
O_FILES := $(filter-out $(MAIN_OBJ), $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.cpp=.o))))
UT_O_FILES := $(addprefix $(UTOBJ_DIR)/,$(notdir $(UT_FILES:.cpp=.o)))
#UT_O_FILES := $(filter-out $(UTMAIN_OBJ), $(addprefix $(UTOBJ_DIR)/,$(notdir $(UT_FILES:_ut.cpp=_ut.o))))
CXXFLAGS ?= -Wall -Wextra -Werror -std=c++17 $(APP_INC)

.PHONY: all clean debug

buildut/utmain.o:
	@mkdir -p $(UTOBJ_DIR)
	$(CXX) -c $(UT_SUF)/utmain.cpp -o $@ $(CXXFLAGS)

buildut/lox_ut.o:
	$(CXX) -o $@ -c src/ut/lox_ut.cpp $(CXXFLAGS)

buildut/scanner_ut.o:
	$(CXX) -o $@ -c src/ut/scanner_ut.cpp $(CXXFLAGS)

buildut/token_ut.o:
	$(CXX) -o $@ -c src/ut/token_ut.cpp $(CXXFLAGS)

build/lox.o:
	$(CXX) -o $@ -c src/lox.cpp  $(CXXFLAGS)

build/scanner.o:
	$(CXX) -o $@ -c src/scanner.cpp  $(CXXFLAGS)

build/token.o:
	$(CXX) -o $@ -c src/token.cpp  $(CXXFLAGS)


ut: $(UT_O_FILES) $(O_FILES)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(UT_INC)

lox: $(O_FILES) $(MAIN_OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

all: ut lox
	

clean:
	$(RM) -r $(UTOBJ_DIR) $(OBJ_DIR) ut lox

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(OBJ_DIR)
	$(CXX) -c -o $@ $(SRC_DIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)

debug:
	@echo $(SRC_FILES)
	@echo $(O_FILES)
	@echo $(UT_O_FILES)
	@echo $(UT_O_FILES) $(O_FILES)
