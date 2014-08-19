

#include <stdio.h>
#include <conio.h>

#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL
#define UMASK 0x80000000UL
#define LMASK 0x7fffffffUL 
#define MIXBITS(u,v) ( ((u) & UMASK) | ((v) & LMASK) )
#define TWIST(u,v) ((MIXBITS(u,v) >> 1) ^ ((v)&1UL ? MATRIX_A : 0UL))

static unsigned long state[N];
static int left = 1;
static int initf = 0;
static unsigned long *next;

void init_genrand(unsigned long s)
{
	int j;
	state[0] = s & 0xffffffffUL;
	for (j = 1; j<N; j++) {
		state[j] = (1812433253UL * (state[j - 1] ^ (state[j - 1] >> 30)) + j);
		state[j] &= 0xffffffffUL;
	}
	left = 1; initf = 1;
}

void init_by_array(unsigned long init_key[], int key_length)
{
	int i, j, k;
	init_genrand(19650218UL);
	i = 1; j = 0;
	k = (N>key_length ? N : key_length);
	for (; k; k--) {
		state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1664525UL))
			+ init_key[j] + j;
		state[i] &= 0xffffffffUL;
		i++; j++;
		if (i >= N) { state[0] = state[N - 1]; i = 1; }
		if (j >= key_length) j = 0;
	}
	for (k = N - 1; k; k--) {
		state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1566083941UL))
			- i;
		state[i] &= 0xffffffffUL;
		i++;
		if (i >= N) { state[0] = state[N - 1]; i = 1; }
	}

	state[0] = 0x80000000UL;
	left = 1; initf = 1;
}

static void next_state(void)
{
	unsigned long *p = state;
	int j;
	if (initf == 0) init_genrand(5489UL);

	left = N;
	next = state;

	for (j = N - M + 1; --j; p++)
		*p = p[M] ^ TWIST(p[0], p[1]);

	for (j = M; --j; p++)
		*p = p[M - N] ^ TWIST(p[0], p[1]);

	*p = p[M - N] ^ TWIST(p[0], state[0]);
}

unsigned long genrand_int32(void)
{
	unsigned long y;

	if (--left == 0) next_state();
	y = *next++;

	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}

long genrand_int31(void)
{
	unsigned long y;

	if (--left == 0) next_state();
	y = *next++;

	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return (long)(y >> 1);
}

double genrand_real1(void)
{
	unsigned long y;

	if (--left == 0) next_state();
	y = *next++;

	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return (double)y * (1.0 / 4294967295.0);
}

double genrand_real2(void)
{
	unsigned long y;

	if (--left == 0) next_state();
	y = *next++;

	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return (double)y * (1.0 / 4294967296.0);
}

double genrand_real3(void)
{
	unsigned long y;

	if (--left == 0) next_state();
	y = *next++;

	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return ((double)y + 0.5) * (1.0 / 4294967296.0);
}

double genrand_res53(void)
{
	unsigned long a = genrand_int32() >> 5, b = genrand_int32() >> 6;
	return(a*67108864.0 + b)*(1.0 / 9007199254740992.0);
}

int main(void)
{
	int i;
	unsigned long init[4] = { 0x123, 0x234, 0x345, 0x456 }, length = 4;
	init_by_array(init, length);
	printf("1000 outputs of genrand_int32()\n");
	for (i = 0; i<1000; i++) {
		printf("%10lu ", genrand_int32());
		if (i % 5 == 4) printf("\n");
	}
	printf("\n1000 outputs of genrand_real2()\n");
	for (i = 0; i<1000; i++) {
		printf("%10.8f ", genrand_real2());
		if (i % 5 == 4) printf("\n");
	}

	_getch();
	return 0;
}
