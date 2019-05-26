CXX=g++-9
MKDIR_P ?= mkdir -p

DEBUGFLAGS ?= -Wall -Wextra -Werror
CXXFLAGS ?= $(INC_FLAGS) $(DEBUGFLAGS) -MMD -MP -std=c++17

ut: src/ut.cpp src/lox.cpp
	$(MKDIR_P) src/ build/
	$(CXX) -o bin/ut src/ut.cpp src/lox.cpp -I./src -I./src/lib $(CXXFLAGS)
