#include <stdio.h>
#include <math.h>

const logical_memory = 32;
const page_size = 4;
const logical_address_space = 8;


int main()
{
	int ram[] = {3, 5, 6, 2, 6, 1, 11, 10, 6, 100, 1, -11, 77, 34, 19, 9, 22, 10, 6, 33, 12, 06, 28, 68,29, 28, 59, 22, 85, 36};
	int page_table[] = {4, 6, 7, 0, 2, 1, 3, 5};

	printf("enter the logical memory address\n");

	int logical_address;
	
	scanf("%d",&logical_address);

	int p = logical_address/page_size;
	int d = logical_address%page_size;

/*	int physical_address = (logical_address*frame_no)+offset; 


	printf("logical_address: %d\nPhysical address: %d\n",logical_address,physical_address );
*/

	printf("Data is: %d\n",ram[page_table[p]*page_size+d-1]);

	return 0;
}