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

#ifndef __RANDGEN_H__
#define __RANDGEN_H__

extern "C" class random_gen
{
public:
	random_gen();
	int next();
	int next(int max);
	int next(int min,int max);
	double next_double();
private:
	unsigned long maxlong;
};

#endif