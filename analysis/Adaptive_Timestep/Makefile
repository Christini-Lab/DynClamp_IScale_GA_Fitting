CXXFLAGS = -O3 -g -fopenmp -std=c++11
LFLAGS =
LIBS =

MODEL_SRC_DIR = ../../lib/LivRudy2009/src/
MODEL_SRCFILES := $(wildcard $(MODEL_SRC_DIR)*.cpp)
MODEL_OBJFILES := $(patsubst %.cpp,%.o,$(wildcard $(MODEL_SRC_DIR)*.cpp))

SRCFILES = $(MODEL_SRCFILES) main.cpp
OBJFILES = $(MODEL_OBJFILES)

EXEC = Model_Simulation

all: $(EXEC)
.PHONY: all clean

# Automatically determine dependencies of source files
depend: .depend
.depend: $(SRCFILES)
	$(CXX) $(CXXFLAGS) -MM $^ > ./.depend;
-include .depend

$(EXEC): $(OBJFILES) main.cpp
	$(CXX) $(CXXFLAGS) $(LFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f *.o $(OBJFILES) $(EXEC) .depend
