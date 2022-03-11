#include <iostream>
#include <string>
#include <cstdlib>

#include "dataStructures.hpp"
#include "policies.hpp"

void lru(char const *argv[])
{
	std::string trace_file = argv[1], debug_mode = argv[4];
	int nframes = atoi(argv[2]);

	Buffer lru(nframes);

	std::ifstream infile(trace_file);

	std::string rw;
	std::string addr;

	while (infile >> addr >> rw) {
		PageTableEntry new_pte(rw, addr);
		if (lru.lruCheckBuffer(new_pte)) {
			lru.lruReplaceR(new_pte);
		} else {
			lru.lruAdd(new_pte);
		}
		lru.trace_count++;
	}
	lru.printBufferData();
}