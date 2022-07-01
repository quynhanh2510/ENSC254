// Copyright (c) Craig Scratchley 2020   wcs (AT) sfu (DOT) ca
#include <algorithm> // for std::min/max
#include "carried_primitive.hpp"

using primitives::carry;
using UInt = primitives::carried_primitive;
using std::min;
using std::max;

//typedef unsigned int bigNumN[];
typedef UInt bigNumN[];

// use a C interface to simplify calling the code from assembly.
extern "C" int bigAdd(bigNumN bigN0PC, const bigNumN bigN1PC, unsigned int maxN0Size);

// c++ code involving access to a simulated carry flag
// returns -1 for error in inputs, 1 if overflow/carry-out and 0 if no overflow/carry-out
int bigAdd(bigNumN bigN0P, const bigNumN bigN1P, unsigned int maxN0Size)
{
#define sizeBigN0P  bigN0P[0]
#define sizeBigN1P  bigN1P[0]

	unsigned index;

	// global variable in primitives namespace
	carry = 0; // this is a global variable representing the carry flag.

	if (max(sizeBigN0P, sizeBigN1P) > maxN0Size)
		return -1; // error condition
	for (index=1; index <= min(sizeBigN0P, sizeBigN1P); ++index) {
		// bigN0P[index] += bigN1P[index] + carry; // this line would end up in C++ as 2 "additions": +, +=
		UInt intermediate = bigN1P[index] + carry; // should update carry
		unsigned carryHold = carry; 	// hold the carry status resulting from adding the carry
		bigN0P[index] += intermediate; 	// should update carry
		carry |= carryHold; 			// carry should also be set if carryHold is 1
	};

	if (sizeBigN0P < sizeBigN1P) {
		for (; index <= sizeBigN1P; ++index)
			bigN0P[index] = bigN1P[index] + carry; // should update carry (adcs ...)
		sizeBigN0P = sizeBigN1P;
	}
	else
		for (; index <= sizeBigN0P; ++index)
			if (!carry)
				return 0;
			else
				bigN0P[index] += carry; // should update carry (adcs ...)

	if (sizeBigN0P != maxN0Size) {
		bigN0P[index] = carry;
		sizeBigN0P += carry; // carry will be cleared
	}
	return carry;
}

