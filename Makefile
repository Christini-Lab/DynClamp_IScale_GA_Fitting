CXXFLAGS = -O3 -g -std=c++11 #-fopenmp
LFLAGS =
LIBS =

GA_SRC_DIR = lib/Genetic_Algorithm/src/
GA_SRCFILES := $(wildcard $(GA_SRC_DIR)*.cpp)
GA_OBJFILES := $(patsubst %.cpp,%.o,$(wildcard $(GA_SRC_DIR)*.cpp))

MODEL_SRC_DIR = lib/LivRudy2009/src/
MODEL_SRCFILES := $(wildcard $(MODEL_SRC_DIR)*.cpp)
MODEL_OBJFILES := $(patsubst %.cpp,%.o,$(wildcard $(MODEL_SRC_DIR)*.cpp))

SRCFILES = $(GA_SRCFILES) $(MODEL_SRCFILES) main.cpp
OBJFILES = $(GA_OBJFILES) $(MODEL_OBJFILES)

EXEC = GA_Fitting

all: $(EXEC)
.PHONY: all clean

# Automatically determine dependencies of source files
depend: .depend
.depend: $(SRCFILES)
	$(CXX) $(CXXFLAGS) -MM $^ >> ./.depend;
-include .depend

$(EXEC): $(OBJFILES) main.cpp
	$(CXX) $(CXXFLAGS) $(LFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f *.o $(OBJFILES) $(EXEC) .depend
