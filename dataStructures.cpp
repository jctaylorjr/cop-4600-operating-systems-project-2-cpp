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

unsigned int PageTableEntry::addrStrtoUnsigned(std::string str)
{
	return std::stoul(str, nullptr, 16);
}

void PageTableEntry::generateVPN()
{
	this->vpn = this->addr >> 12;
}

void Buffer::printBufferData()
{
	std::cout << "Memory frames: " << nframes
		  << "\nTrace count: " << trace_count
		  << "\nRead count: " << read_count
		  << "\nWrite count: " << write_count << std::endl;
}

// void Buffer::checkForWBit(PageTableEntry pte)
// {
// 	if (!pte.rw.compare("W")) {
// 		// read_count++;
// 	}
// }

/**************************** FIFO ****************************/

// fifo case 1
bool Buffer::fifoCheckBuffer(PageTableEntry pte)
{
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i].vpn == pte.vpn) {
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

/**************************** LRU ****************************/

bool Buffer::lruCheckBuffer(PageTableEntry pte)
{
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i].vpn == pte.vpn) {
			PageTableEntry reinsert = buffer[i];
			buffer.erase(buffer.begin() + i);
			buffer.push_back(reinsert);
			return true;
		}
	}
	return false;
}

void Buffer::lruReplaceR(PageTableEntry pte)
{
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i].vpn == pte.vpn && buffer[i].rw.compare(pte.rw) &&
		    !pte.rw.compare("W")) {
			buffer[i].rw = "W";
		}
	}
}

// lru case 2 and 3
void Buffer::lruAdd(PageTableEntry pte)
{
	// solution 3
	if (buffer.size() >= nframes) {
		if (buffer[0].rw.compare("R")) {
			write_count++;
		}
		buffer.pop_front();
	}
	read_count++;
	// solution 2
	buffer.push_back(pte);
}

/**************************** VMS ****************************/