CXXFLAGS ?= -ggdb -Wall -Wextra -Werror -std=c++2a

EXENAME := $(patsubst ./src/%/,%,$(dir $(wildcard ./src/*/.)))
EXE := bin/$(EXENAME)
UTEXE := bin/$(EXENAME).ut

#### FIXME: FOR NOW STATIC MAKEFILE WITH SCANNER, PARSER LOX SEPARATE ####

SCANNER_CCPS := $(subst src/,build/,$(wildcard src/lox/scanner/*.cpp))
SCANNER_OBJS := $(SCANNER_CCPS:.cpp=.o)

SCANNER_UT_CCPS := $(subst src/,build/,$(wildcard src/lox/scanner/ut/*.cpp))
SCANNER_UT_OBJS := $(SCANNER_UT_CCPS:.cpp=.o)

bin/lox.scanner.ut: build/utmain.o build/lox/scanner.ut.o
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS)

build/lox/scanner.o: $(SCANNER_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

build/lox/scanner.ut.o: build/lox/scanner.o $(SCANNER_UT_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

build/lox/scanner/%.o: src/lox/scanner/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)include $(CXXFLAGS)

build/lox/scanner/ut/%.o: src/lox/scanner/ut/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)../include -Isrc/ $(CXXFLAGS)

#### FIXME: FOR NOW STATIC MAKEFILE WITH SCANNER, PARSER LOX SEPARATE ####

parser_CCPS := $(subst src/,build/,$(wildcard src/lox/parser/*.cpp))
parser_OBJS := $(parser_CCPS:.cpp=.o)

parser_UT_CCPS := $(subst src/,build/,$(wildcard src/lox/parser/ut/*.cpp))
parser_UT_OBJS := $(parser_UT_CCPS:.cpp=.o)

bin/lox.parser.ut: build/utmain.o build/lox/parser.ut.o
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS)

build/lox/parser.o: $(parser_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

build/lox/parser.ut.o: build/lox/parser.o $(parser_UT_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

build/lox/parser/%.o: src/lox/parser/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)include $(CXXFLAGS)

build/lox/parser/ut/%.o: src/lox/parser/ut/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)../include -Isrc/ $(CXXFLAGS)

#### FIXME: FOR NOW STATIC MAKEFILE WITH SCANNER, PARSER LOX SEPARATE ####

lox_CCPS := $(subst src/,build/,$(wildcard src/lox/*.cpp))
lox_OBJS := $(lox_CCPS:.cpp=.o)

lox_UT_CCPS := $(subst src/,build/,$(wildcard src/lox/ut/*.cpp))
lox_UT_OBJS := $(lox_UT_CCPS:.cpp=.o)

bin/lox.ut: build/utmain.o build/lox.ut.o
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(CXXFLAGS)

build/lox.o: $(lox_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

build/lox.ut.o: build/lox.o $(lox_UT_OBJS)
	@mkdir -p $(dir $@)
	$(LD) -o $@ -r $^

build/lox/%.o: src/lox/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)include $(CXXFLAGS)

build/lox/ut/%.o: src/lox/ut/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)../include -Isrc/ $(CXXFLAGS)

####

bin/lox: build/lox/

#### MAIN OBJS

build/%main.o: src/%main.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $^ -I$(dir $^)include $(CXXFLAGS)

#### PHONY
.PHONY: all cleanall clean

all: $(UTEXE) $(EXE)

clean:
	$(RM) -r $(OFILES) $(UTOFILES) $(BINDIR)

cleanall: clean
	$(RM) -r $(BUILDDIR) $(BINDIR)
