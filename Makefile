CXX=g++
CXXFLAGS=-W -Wall
LDFLAGS="-lpcap -readline"
EXEC=airplay-ng

all: airplay-ng

airplay-ng:
	rm -rf airplay-ng
	$(CXX) -o airplay-ng source/airsniff-ng.cpp -lpcap -lreadline

