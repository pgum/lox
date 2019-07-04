CXXFLAGS ?= -ggdb -Wall -Wextra -Werror -std=c++2a
NAME := $(patsubst ./src/%/,%,$(dir $(wildcard ./src/*/.)))

BUILD := build
BIN := bin

#### SYSTEM BUILD
COMPONENTS := $(filter-out include,$(filter-out ut,$(patsubst ./src/$(NAME)/%/,%,$(dir $(wildcard ./src/$(NAME)/*/.)))))
COMPONENTS_OBJS := $(addprefix $(BUILD)/$(NAME)/,$(COMPONENTS))
COMPONENTS_OBJS := $(addsuffix .o,$(COMPONENTS_OBJS))

UT_COMPONENTS_OBJS := $(addprefix $(BUILD)/$(NAME)/,$(COMPONENTS))
UT_COMPONENTS_OBJS := $(addsuffix .ut.o,$(UT_COMPONENTS_OBJS))

$(BUILD)/$(NAME).o: $(COMPONENTS_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

$(BIN)/$(NAME): $(BUILD)/$(NAME).o $(BUILD)/main.o
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(BIN)/$(NAME).ut: $(UT_COMPONENTS_OBJS) $(COMPONENTS_OBJS) $(BUILD)/utmain.o
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS)

ifndef COMPONENT
$(BUILD)/$(NAME)/%.o:
	$(MAKE) $@ COMPONENT=$(shell basename $@ | cut -f1 -d.)
endif


ifdef COMPONENT
#### COMPONENT $(BUILD)
CPPS := $(wildcard src/$(NAME)/$(COMPONENT)/*.cpp)
OBJS := $(subst src/,$(BUILD)/,$(CPPS:.cpp=.o))

COMPONENT_OBJ := $(BUILD)/$(NAME)/$(COMPONENT).o

UT_OBJS := $(subst src/,$(BUILD)/,$(wildcard src/$(NAME)/$(COMPONENT)/ut/*.cpp))
UT_OBJS := $(UT_OBJS:.cpp=.o)

UT_COMPONENT_OBJ := $(BUILD)/$(NAME)/$(COMPONENT).ut.o

UTEXE := $(BIN)/$(NAME).$(COMPONENT).ut

$(UTEXE): $(UT_COMPONENT_OBJ) $(OBJS) $(BUILD)/utmain.o
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(UT_COMPONENT_OBJ): $(COMPONENT_OBJ) $(UT_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

$(COMPONENT_OBJ): $(OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

$(BUILD)/$(NAME)/$(COMPONENT)/%.o: src/$(NAME)/$(COMPONENT)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)include $(CXXFLAGS)

$(BUILD)/$(NAME)/$(COMPONENT)/ut/%.o: src/$(NAME)/$(COMPONENT)/ut/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)../include -Isrc/ $(CXXFLAGS)
endif

#### MAINS

$(BUILD)/utmain.o: src/utmain.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -Iinclude $(CXXFLAGS)

$(BUILD)/main.o: src/main.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -Isrc/$(NAME)/include $(CXXFLAGS)

.PHONY: all cleanall clean

all: $(BIN)/$(NAME) $(BIN)/$(NAME).ut

clean:
	$(RM) -rf $(BUILD)/$(NAME)/ $(BUILD)/$(NAME).o 

cleanall: clean
	$(RM) -r $(BUILD)/ $(BIN)/

