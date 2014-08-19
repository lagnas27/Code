#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

static unsigned int index = 0;
static unsigned long state[16];

unsigned long WELLRNG512(void)
{
	srand(time(NULL));
	
	for (int i = 0; i < 16; i++)
		state[i] = rand();
	
	unsigned long a, b, c, d;
	a = state[index];
	c = state[(index + 13) & 15];
	b = a^c ^ (a << 16) ^ (c << 15);
	c = state[(index + 9) & 15];
	c ^= (c >> 11);
	a = state[index] = b^c;
	d = a ^ ((a << 5) & 0xDA442D20UL);
	index = (index + 15) & 15;
	a = state[index];
	state[index] = a^b^d ^ (a << 2) ^ (b << 18) ^ (c << 28);
	return state[index];
}

int main()
{
	int *a = new int[6];
	for (int i = 0; i < 6; i++)
	{
		a[i] = WELLRNG512();
		cout << a[i] << " ";
	}
	_getch();
	return 0;
}
