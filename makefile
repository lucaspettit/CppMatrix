# Declare compile commands
CXX			 = g++
CXXFLAGS = -Wall -g -std=c++11

# Declare variables
MATRIX   = Matrix
TESTNAME = test
OBJS     = $(MATRIX).o

# Command to make test executable
$(TESTNAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(TESTNAME).cpp $(OBJS) -o $(TESTNAME)

# Command to make Matrix binary (can be build independently from test prog.)
$(MATRIX):
	$(CXX) $(CXXFLAGS) -c $(MATRIX).cpp -o $(MATRIX).o

# Generic binary building command (used by $(TESTNAME))
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $<

# Clean out prebuild binaries/executables
clean:
	rm *.o
	rm $(TESTNAME)
