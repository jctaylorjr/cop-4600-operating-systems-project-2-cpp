#include <iostream>
#include <string>
#include <cstdlib>

#include "dataStructures.hpp"

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
		if (fifo.checkBuffer(new_pte)) {
			fifo.fifoReplaceR(new_pte);
		} else {
			fifo.fifoAdd(new_pte);
		}
		fifo.trace_count++;
	}
	std::cout << "Memory frames: " << fifo.nframes
		  << "\nTrace count: " << fifo.trace_count
		  << "\nRead count: " << fifo.read_count
		  << "\nWrite count: " << fifo.write_count << std::endl;
}