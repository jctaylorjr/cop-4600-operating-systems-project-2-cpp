#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	// 2^10 = 1KB = 1024B, 2^2 = 4B, 4KB = 4096B = 2^12
	unsigned int virtual_address = 21; //010101b
	unsigned int vpn_mask = 0x30; //110000b
	unsigned int vpn = (virtual_address & vpn_mask) >> 4; //010000 >> 000001
	// unsigned int PTE_addr ==
	printf("vpn: %d\n", vpn);

	unsigned int sixfour = 32;
	printf("base 10: %d\nbase 16: %x\nbinary: ", sixfour, sixfour);

	// shifting 1 to left 31 times, masking number in question, then reducing 1 bit
	for (unsigned int i = 1 << 31; i > 0; i = i >> 1) {
		sixfour &i ? printf("1") : printf("0");
	}
	printf("\n");
	return 0;
}
