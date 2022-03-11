#include <iostream>
#include <string>
#include <cstdlib>

#include "dataStructures.hpp"
#include "policies.hpp"

void FIFO(char const *argv[])
{
	std::string trace_file = argv[1], debug_mode = argv[4];
	int nframes = atoi(argv[2]);

	Buffer fifo(nframes);

	std::ifstream infile(trace_file);

	std::string rw;
	std::string addr;

	while (infile >> addr >> rw) {
		PageTableEntry new_pte(rw, addr);
		PageTableEntry popped_pte = new_pte;
		if (fifo.fifoCheckBuffer(new_pte)) {
			fifo.fifoReplaceR(new_pte);
		} else {
			popped_pte = fifo.addPte(new_pte);
			if (popped_pte.rw.compare("R") &&
			    popped_pte.addr != new_pte.addr) {
				fifo.write_count++;
			}
			fifo.read_count++;
		}
		fifo.trace_count++;
	}
	fifo.printBufferData();
}