EXE := lox
SRCDIR := src
BUILDDIR := build
FILES := $(filter-out $(SRCDIR)/main.cpp,$(wildcard $(SRCDIR)/*.cpp))
MAIN_OBJ := $(BUILDDIR)/main.o
OFILES := $(addprefix $(BUILDDIR)/,$(notdir $(FILES:.cpp=.o)))
UTEXE := ut
UTSRCDIR := $(SRCDIR)/ut
UTBUILDDIR := $(BUILDDIR)/ut
UTFILES := $(wildcard $(UTSRCDIR)/*_ut.cpp)
UTMAIN_OBJ := $(UTBUILDDIR)/utmain.o
UTOFILES := $(addprefix $(UTBUILDDIR)/,$(notdir $(UTFILES:.cpp=.o)))

CXXFLAGS ?= -Wall -Wextra -Werror -std=c++2a -I $(SRCDIR)

CXX += -ggdb

.PHONY: all clean fresh

all: $(UTEXE) $(EXE)

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

clean:
	clear
	$(RM) -rf $(BUILDDIR) $(UTEXE) $(EXE)

eraseNonMain:
	clear
	$(RM) $(OFILES) $(UTOFILES) $(UTEXE) $(EXE)

fresh: | eraseNonMain all
	./ut

%.ut: $(UTMAIN_OBJ) $(BUILDDIR)/%.o $(UTBUILDDIR)/%_ut.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -I $(UTSRCDIR)
