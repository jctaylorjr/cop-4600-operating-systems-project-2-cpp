#include <iostream>
#include <string>
#include <cstdlib>

#include "dataStructures.hpp"
#include "policies.hpp"

void fifo(char const *argv[])
{
	std::string trace_file = argv[1], debug_mode = argv[4];
	int nframes = atoi(argv[2]);

	Buffer fifo(nframes);

	std::ifstream infile(trace_file);

	std::string rw;
	std::string addr;

	while (infile >> addr >> rw) {
		PageTableEntry new_pte(rw, addr);
		if (fifo.fifoCheckBuffer(new_pte)) {
			fifo.fifoReplaceR(new_pte);
		} else {
			fifo.fifoAdd(new_pte);
		}
		fifo.trace_count++;
	}
	fifo.printBufferData();
}