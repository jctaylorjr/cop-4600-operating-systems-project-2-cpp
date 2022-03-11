#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <deque>
#include <fstream>
#include <iostream>
#include <string>

class PageTableEntry {
    private:
	unsigned int addrStrtoUnsigned(std::string str);
	void generateVPN();

    public:
	unsigned int addr = 0;
	std::string rw;
	unsigned int vpn = 0;
	PageTableEntry(std::string rw, std::string addr);
	~PageTableEntry();
};

class Buffer {
    private:
    public:
	int trace_count = 0;
	int read_count = 0;
	int write_count = 0;
	int nframes = 0;
	std::deque<PageTableEntry> buffer;

	Buffer(int nframes);
	~Buffer();
	void printBufferData();
	// FIFO
	bool fifoCheckBuffer(PageTableEntry pte);
	void fifoAdd(PageTableEntry pte);
	void fifoReplaceR(PageTableEntry pte);
	// LRU
	bool lruCheckBuffer(PageTableEntry pte);
	void lruAdd(PageTableEntry pte);
	void lruReplaceR(PageTableEntry pte);
	// VMS
};

// void checkForWBit(PageTableEntry pte);
#endif