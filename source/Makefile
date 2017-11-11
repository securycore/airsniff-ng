CXX=g++
CXXFLAGS=-W -Wall
LDFLAGS=-lpcap
EXEC=airplay-ng

all: airplay-ng

airplay-ng: Arp.o ArpSpoofing.o Ethernet.o NetworkUtilities.o Packet.o
	$(CXX) -o arppoisonning Arp.o ArpSpoofing.o Ethernet.o NetworkUtilities.o Packet.o arp_main.cpp $(CXXFLAGS) $(LDFLAGS)

