SRCDIR := src
BUILDDIR := build
FILES := $(filter-out $(SRCDIR)/main.cpp,$(wildcard $(SRCDIR)/*.cpp))
MAIN_OBJ := $(BUILDDIR)/main.o
OFILES := $(addprefix $(BUILDDIR)/,$(notdir $(FILES:.cpp=.o)))

UTSRCDIR := $(SRCDIR)/ut
UTBUILDDIR := buildut
UTFILES := $(wildcard $(UTSRCDIR)/*_ut.cpp)
UTMAIN_OBJ := $(UTBUILDDIR)/utmain.o
UTOFILES := $(addprefix $(UTBUILDDIR)/,$(notdir $(UTFILES:.cpp=.o)))

CXXFLAGS ?= -Wall -Wextra -Werror -std=c++17 -I $(SRCDIR)

.PHONY: all clean tidy

all: ut lox

lox: $(MAIN_OBJ) $(OFILES)
	@echo Building MAIN binary
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(MAIN_OBJ): $(SRCDIR)/main.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -o $@ -c $(SRCDIR)/main.cpp $(CXXFLAGS)

build/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -o $@ -c $(SRCDIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)

ut: $(UTMAIN_OBJ) $(UTOFILES) $(OFILES)
	@echo Building UT binary
	$(CXX) -o $@ $^ $(CXXFLAGS) -I $(UTSRCDIR)

$(UTMAIN_OBJ): $(UTSRCDIR)/utmain.cpp
	@mkdir -p $(UTBUILDDIR)
	$(CXX) -o $@ -c $^ $(CXXFLAGS)

buildut/%.o: $(UTSRCDIR)/%.cpp
	@mkdir -p $(UTBUILDDIR)
	$(CXX) -o $@ -c $(UTSRCDIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)

clean:
	$(RM) -r $(UTBUILDDIR) $(BUILDDIR) -r ut lox

