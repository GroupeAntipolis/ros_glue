//
//
//  	G.L.U.E. by M.C.G. 2015 
//
//  	Glue stands for 
// 	Genetically Leaded Universal Evaluator.
//
// 		Add some glue in your code... 
//
//
//
//	Here is a RNG called WELL512, designed by the designers of 
//	Mersenne, developed 10 years later, and an all around better
//	choice for games. The code is put in the public domain by Dr.
//	Chris Lomont. He claims this implementation is 40% faster
//	than Mersenne, does not suffer from poor diffusion and
//	trapping when the state contains many 0 bits, and is clearly
//	a lot simpler code. It has a period of 2^512; a PC takes over
//	10^100 years to cycle through the states, so it is large enough.
//
//	Here is a paper overviewing PRNGs where I found the
//	WELL512 implementation.
//	http://www.lomont.org/Math/Papers/2008/Lomont_PRNG_2008.pdf

#include "random_gen.h"
//#include <stdlib.h> 
#include <cstddef>
#include <math.h>
/* initialize state to random bits */
static unsigned long state[16];
/* init should also reset this to 0 */
static unsigned int index = 0;

/* return 32 bit random number */
unsigned long WELLRNG512(void)
{
	unsigned long a, b, c, d;
	a = state[index];
	c = state[(index+13)&15];
	b = a^c^(a<<16)^(c<<15);
	c = state[(index+9)&15];
	c ^= (c>>11);
	a = state[index] = b^c;
	d = a^((a<<5)&0xDA442D24UL);
	index = (index + 15)&15;
	a = state[index];
	state[index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
	return state[index];
}

// random_gen object members

	random_gen::random_gen()
	{
		maxlong=(unsigned long)pow(2,512);
		// here we must initialise state because
		// our compiler fill state with 0 at startup
	    for(size_t i = 0; i < sizeof(state)/sizeof(state[0]); i++)
	    {
	    	state[i] = (i << (24 + (i & 5))) ^ (i << 7) ^ (i << 6) ^ (i >> 2);
	    }
	}
	// return a 32bits random number
	int random_gen::next()
	{
		return WELLRNG512();
	};

	// return a 32bits random number
	// between 0 and max
	int random_gen::next(int max)
	{
		return ((double)max/maxlong)*WELLRNG512();
	};

	// return a 32bits random number
	// between min and max
	int random_gen::next(int min,int max)
	{
		return next(max-min)+min;
	};

	// return a 32bits random floating number
	double random_gen::next_double()
	{
		return (1.0/maxlong)*WELLRNG512();
	};