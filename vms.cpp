#include <iostream>
#include <string>
#include <cstdlib>

#include "dataStructures.hpp"
#include "policies.hpp"

void VMS(char const *argv[])
{
	std::string trace_file = argv[1], debug_mode = argv[5];
	int nframes = atoi(argv[2]), p = atoi(argv[4]);

	int secondary_size = (nframes * p) / 100;
	int primary_size = nframes - secondary_size;
	Buffer lru(secondary_size);
	Buffer fifo(primary_size);

	if (!primary_size) {
		LRU(argv);
		exit(EXIT_SUCCESS);
	} else if (!secondary_size) {
		FIFO(argv);
		exit(EXIT_SUCCESS);
	}

	std::ifstream infile(trace_file);

	std::string rw;
	std::string addr;

	while (infile >> addr >> rw) {
		PageTableEntry new_pte(rw, addr);
		PageTableEntry popped_pte = new_pte;
		if (fifo.fifoCheckBuffer(new_pte)) {
			fifo.fifoReplaceR(new_pte);
		} else if (lru.lruCheckBuffer(new_pte)) {
			popped_pte = lru.lruReplaceR(new_pte);
			lru.buffer.pop_back();
			lru.addPte(fifo.addPte(popped_pte));
		} else {
			popped_pte = lru.addPte(fifo.addPte(new_pte));
			if (popped_pte.rw.compare("R") &&
			    popped_pte.vpn != new_pte.vpn) {
				lru.write_count++;
			}
			lru.read_count++;
		}
		lru.trace_count++;
	}
	lru.nframes += fifo.nframes;
	lru.printBufferData();
}