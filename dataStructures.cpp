#include "dataStructures.hpp"

PageTableEntry::PageTableEntry(std::string rw, std::string addr)
{
	this->addr = PageTableEntry::addrStrtoUnsigned(addr);
	this->rw = rw;
	PageTableEntry::generateVPN();
}

PageTableEntry::~PageTableEntry()
{
}

Buffer::Buffer(int nframes)
{
	this->nframes = nframes;
}

Buffer::~Buffer()
{
}

// fifo solution 1
void Buffer::checkForWBit(PageTableEntry pte)
{
	if (!pte.rw.compare("W")) {
		// read_count++;
	}
}

// fifo case 1
bool Buffer::checkBuffer(PageTableEntry pte)
{
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i].vpn == pte.vpn) {
			checkForWBit(buffer[i]);
			return true;
		}
	}
	return false;
}

void Buffer::fifoReplaceR(PageTableEntry pte)
{
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i].vpn == pte.vpn && buffer[i].rw.compare(pte.rw) &&
		    !pte.rw.compare("W")) {
			buffer[i].rw = "W";
		}
	}
}

// fifo case 2 and 3
void Buffer::fifoAdd(PageTableEntry pte)
{
	// solution 3
	if (buffer.size() >= nframes) {
		if (buffer[0].rw.compare("R")) {
			write_count++;
		}
		buffer.pop_front();
	}
	read_count++;
	// fifo solution 2
	buffer.push_back(pte);
}

unsigned int PageTableEntry::addrStrtoUnsigned(std::string str)
{
	return std::stoul(str, nullptr, 16);
}

void PageTableEntry::generateVPN()
{
	this->vpn = this->addr >> 12;
}