#include <iostream>
#include <string>
#include <cstdlib>

#include "dataStructures.hpp"
#include "policies.hpp"

void LRU(char const *argv[])
{
	std::string trace_file = argv[1], debug_mode = argv[4];
	int nframes = atoi(argv[2]);

	Buffer lru(nframes);

	std::ifstream infile(trace_file);

	std::string rw;
	std::string addr;

	while (infile >> addr >> rw) {
		PageTableEntry new_pte(rw, addr);
		PageTableEntry popped_pte = new_pte;
		if (lru.lruCheckBuffer(new_pte)) {
			lru.lruReplaceR(new_pte);
		} else {
			popped_pte = lru.addPte(new_pte);
			if (popped_pte.rw.compare("R") &&
			    popped_pte.addr != new_pte.addr) {
				lru.write_count++;
			}
			lru.read_count++;
		}
		lru.trace_count++;
	}
	lru.printBufferData();
}