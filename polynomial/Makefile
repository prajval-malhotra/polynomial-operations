CXXFLAGS= -std=c++14

poly: main.o polynomial.o
	g++ main.o polynomial.o rational.o -o poly

main.o: main.cc polynomial.h
	g++ ${CXXFLAGS} -c main.cc

poly.o: polynomial.cc polynomial.h
	g++ ${CXXFLAGS} -c polynomial.cc