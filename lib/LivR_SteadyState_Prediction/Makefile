CXXFLAGS = -O3 -g -std=c++11
LFLAGS =
LIBS =

SRCFILES = LivR_SS_Prediction.cpp main.cpp
OBJFILES = LivR_SS_Prediction.o

EXEC = Predict

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
