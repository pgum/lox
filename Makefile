CXX=g++-9
MKDIR_P ?= mkdir -p

DEBUGFLAGS ?= -Wall -Wextra -Werror
CXXFLAGS ?= $(INC_FLAGS) $(DEBUGFLAGS) -MMD -MP -std=c++17

ut:
	$(MKDIR_P) src/ build/ bin/
	$(CXX) -c src/lox.cpp -o build/lox.o $(CXXFLAGS)
	$(CXX) -c src/ut.cpp -o build/ut.o $(CXXFLAGS)
	$(CXX) -o bin/ut build/ut.o build/lox.o $(CXXFLAGS)
