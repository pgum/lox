EXENAME := lox
UTNAME := ut
SRCDIR := src
BUILDDIR := build
BINDIR := bin
CXXFLAGS ?= -ggdb -Wall -Wextra -Werror -std=c++2a -I $(SRCDIR)/include

UTSRCDIR := $(SRCDIR)/ut
UTBUILDDIR := $(BUILDDIR)/ut
EXE := $(BINDIR)/$(EXENAME)
UTEXE := $(BINDIR)/$(UTNAME)
MAIN_OBJ := $(BUILDDIR)/main.o
UTMAIN_OBJ := $(UTBUILDDIR)/utmain.o
FILES := $(filter-out $(SRCDIR)/main.cpp,$(wildcard $(SRCDIR)/*.cpp))
UTFILES := $(filter-out $(UTSRCDIR)/utmain.cpp,$(wildcard $(UTSRCDIR)/*.cpp))
OFILES := $(addprefix $(BUILDDIR)/,$(notdir $(FILES:.cpp=.o)))
UTOFILES := $(addprefix $(UTBUILDDIR)/,$(notdir $(UTFILES:.cpp=.o)))

.PHONY: all cleanall clean

all: $(UTEXE) $(EXE)

clean:
	$(RM) -r $(OFILES) $(UTOFILES) $(BINDIR)

cleanall: clean
	$(RM) -r $(BUILDDIR) $(BINDIR)

$(BINDIR)/%.ut: $(UTMAIN_OBJ) $(BUILDDIR)/%.o $(UTBUILDDIR)/%.o
	@mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(CXXFLAGS) -I $(UTSRCDIR)

$(UTEXE): $(UTMAIN_OBJ) $(UTOFILES) $(OFILES)
	@mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(CXXFLAGS) -I $(UTSRCDIR)

$(UTMAIN_OBJ): $(UTSRCDIR)/utmain.cpp
	@mkdir -p $(UTBUILDDIR)
	$(CXX) -o $@ -c $^ $(CXXFLAGS)

$(UTBUILDDIR)/%.o: $(UTSRCDIR)/%.cpp
	@mkdir -p $(UTBUILDDIR)
	$(CXX) -o $@ -c $(UTSRCDIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)

$(EXE): $(MAIN_OBJ) $(OFILES)
	@mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(MAIN_OBJ): $(SRCDIR)/main.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -o $@ -c $(SRCDIR)/main.cpp $(CXXFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -o $@ -c $(SRCDIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)

