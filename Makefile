# Makefile for diehard
# Adam Anthony 7/10/16
# To build the shared library
# $ make 
#
# To build the library and the main pogram
# $ make build
#
# To clean the bin/ and build/ directories
# $ make clean

#**** MACRO DEFINITIONS ****#

# Specify the the binary, build, and source directories
BUILDDIR = build
BINDIR = bin
SRCDIR = src
LIBDIR = lib

# Specify header files directory. Note that this must be an absolute
# path to ensure the ROOT dictionary files can find the headers
INCLDIR = $(PWD)/include

# Specify all header files
INCLS = $(INCLDIR)/*.h


# Find all SRC files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
#SRCS += $(wildcard $(SRCDIR)/gui/*.cpp)
#Generate the names/locations for the object files from SRCS
TMP = $(patsubst %.cpp,%.o,$(SRCS))
OBJS = $(subst $(SRCDIR),$(BUILDDIR),$(TMP))

#Test source and object
TESTSRC = test.C
TMP1 = $(patsubst %.C,%.o,$(TESTSRC))
TESTO = $(addprefix $(BUILDDIR)/, $(TMP1))

#Main source and object
MAINSRC = main.C
TMP2 = $(patsubst %.C,%.o,$(MAINSRC))
MAINO = $(addprefix $(BUILDDIR)/, $(TMP2))

# Add various compiler flag
#-w blocks all warning messages
CXXFLAGS = -std=c++11 -fPIC -w -I$(INCLDIR)
SOFLAGS = -O -shared

#Name of generated library
MYLIB = diehard
SO = $(LIBDIR)/lib$(MYLIB).so

# Add linker flags for CAEN libraries (architecture dependent).
LDFLAGS = -Llib

CXX = g++

debug: CXXFLAGS += -DDEBUG -g
test: CXXFLAGS += -DDEBUG -g
debug: build

#***************#
#**** RULES ****#
#***************#

#*************************#
# Rules to build the libraries
default : $(SO)
	@echo "Done"

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp $(INCLS)
	@echo  "Building object file '$@' ..."
	@$(CXX) -g $(CXXFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o : %.C $(INCLS)
	@echo  "Building object file '$@' ..."
	@$(CXX) -DSTANDALONE -g $(CXXFLAGS) -c -o $@ $<

$(SO) : $(OBJS) $(ROOTDICO)
	@echo "Building shared library"
	@$(CXX) $(SOFLAGS) $(LDFLAGS) $^ -o $@

build : $(MAINO) $(SO)
	@echo "Compiling $(MAINSCR)"
	@$(CXX) -DSTANDALONE -g -o main.out $< -l$(MYLIB) $(LDFLAGS)
	@echo "Done"

test: $(TESTO) $(SO)
	@echo "Compiling test macro $(TESTSCR)"
	@$(CXX) -DSTANDALONE -g -o test.out $< -l$(MYLIB) $(LDFLAGS)
	@echo "Done"


# Clean the directory of all build files and binaries
.PHONY: 
clean:
	@echo  "Cleaning up the build and binary ..."
	@rm -f $(BUILDDIR)/*.o *.d $(BUILDDIR)/*Dict.* $(SO) $(TARGET)
	@rm -f $(BUILDDIR)/dict/*.o $(BUILDDIR)/gui/*.o
	@rm -f *Dict*
	@echo "Done"

# Useful notes for the uninitiated:
#
# <target> : <dependency list>
#  --TAB-- <rule>
#
# "$@" == subst. the word to the left of the ":"
# "$^" == subst. the words to the right of ":"
# "$<" == subst. first item in dependency list
