EXE := lox
SRCDIR := src
BUILDDIR := build
FILES := $(filter-out $(SRCDIR)/main.cpp,$(wildcard $(SRCDIR)/*.cpp))
MAIN_OBJ := $(BUILDDIR)/main.o
OFILES := $(addprefix $(BUILDDIR)/,$(notdir $(FILES:.cpp=.o)))
UTEXE := ut
UTSRCDIR := $(SRCDIR)/ut
UTBUILDDIR := $(BUILDDIR)/ut
UTFILES := $(filter-out $(UTSRCDIR)/utmain.cpp,$(wildcard $(UTSRCDIR)/*.cpp))
UTMAIN_OBJ := $(UTBUILDDIR)/utmain.o
UTOFILES := $(addprefix $(UTBUILDDIR)/,$(notdir $(UTFILES:.cpp=.o)))

CXXFLAGS ?= -ggdb -Wall -Wextra -Werror -std=c++2a -I $(SRCDIR)/include

.PHONY: all mains cleanall clean runUT

all: $(UTEXE) $(EXE)

mains: $(MAIN_OBJ) $(UTMAIN_OBJ)

cleanall:
	$(RM) -rf $(BUILDDIR) $(UTEXE) $(EXE)

clean:
	$(RM) $(OFILES) $(UTOFILES) $(UTEXE) $(EXE)

runUT: $(UTEXE)
	./$(UTEXE)

%.ut: $(UTMAIN_OBJ) $(BUILDDIR)/%.o $(UTBUILDDIR)/%_ut.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -I $(UTSRCDIR)

$(UTEXE): $(UTMAIN_OBJ) $(UTOFILES) $(OFILES)
	$(CXX) -o $@ $^ $(CXXFLAGS) -I $(UTSRCDIR)

$(UTMAIN_OBJ): $(UTSRCDIR)/utmain.cpp
	@mkdir -p $(UTBUILDDIR)
	$(CXX) -o $@ -c $^ $(CXXFLAGS)

$(UTBUILDDIR)/%.o: $(UTSRCDIR)/%.cpp
	@mkdir -p $(UTBUILDDIR)
	$(CXX) -o $@ -c $(UTSRCDIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)

$(EXE): $(MAIN_OBJ) $(OFILES)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(MAIN_OBJ): $(SRCDIR)/main.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -o $@ -c $(SRCDIR)/main.cpp $(CXXFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -o $@ -c $(SRCDIR)/$(notdir $(@:.o=.cpp)) $(CXXFLAGS)

