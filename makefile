all: solver.cpp solverFunctions.cpp solver

solver: solver.cpp solverFunctions.cpp
	g++ solver.cpp solverFunctions.cpp -o $@
	
solver.o: solver.cpp solverFunctions.h
	g++ solver.cpp

solverFunctions.o: solverFunctions.cpp solverFunctions.h
	g++ solverFunctions.cpp
clean:
	rm -f *.o solver
