CXX = /usr/bin/g++
LDFLAGS =
CPPFLAGS = 
INC =
CXXFLAGS = -std=c++17 -g -Wall -pedantic -O2 -D_GLIBCXX_DEBUG -fsanitize=address -fopenmp

%.o: %.cpp a4_util.h BLAST_Neighborhood.hpp
	${CXX} ${CXXFLAGS} -I . -c $*.cpp
	
	
aufgabe4_main: BLAST_Neighborhood.o aufgabe4_main.o a4_util.o
	${CXX} ${CXXFLAGS} -I . $^ -o aufgabe4_main

aufgabe4_test: BLAST_Neighborhood.o aufgabe4_test.o a4_util.o
	${CXX} ${CXXFLAGS} -I . $^ -o aufgabe4_test
  
clean: 
	rm *.o
