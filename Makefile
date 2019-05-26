CXX=g++-9
DEBUGFLAGS ?= -Wall -Wextra -Werror
CXXFLAGS ?= $(DEBUGFLAGS) -std=c++17
UTFLAGS ?= -I ./lib -I ./src

run_ut: ut
	./bin/ut

./build:
	mkdir -p ./build

./build/ut.o: ./build
	$(CXX) -c -o $@ ut/ut.cpp $(CXXFLAGS) $(UTFLAGS)

./build/lox.o: ./build
	$(CXX) -c -o $@ src/lox.cpp $(CXXFLAGS)

./build/main.o: ./build
	$(CXX) -c -o $@ src/main.cpp $(CXXFLAGS)

ut: ./build/ut.o ./build/lox.o
	mkdir -p ./bin
	$(CXX) -o ./bin/$@ $^ $(CXXFLAGS)

lox: ./build/lox.o ./build/main.o
	mkdir -p ./bin
	$(CXX) -o ./bin/$@ $^ $(CXXFLAGS)

clean:
	$(RM) -r ./bin ./build
