CXXFLAGS=-g -std=c++14

poly: main.o polynomial.o rational.o
	g++ -g main.o polynomial.o rational.o -o poly

main.o: main.cc polynomial.h rational.h
	g++ ${CXXFLAGS} -c main.cc

poly.o: polynomial.cc polynomial.h
	g++ ${CXXFLAGS} -c polynomial.cc
