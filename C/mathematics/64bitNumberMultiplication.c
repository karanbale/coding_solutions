/*
Multiply two 64 bit numbers such that result will be 128-bit number.
But what if we want to multiply two 64-bit numbers and there is no 128-bit type?
Then we need to do the multiplication by hand. To do that, we split both number in two 32-bit parts.
Let's write "<< 32" as "* shift" to make this easier to read.
Basically if we write the first number as a1 shift + a0 and the second number as b1 shift + b0, then the product is

  (a1 shift + a0) * (b1 shift + b0) ==
  a1 b1 shift shift + a1 b0 shift + a0 b1 shift + a0 b0

The first term is shifted by 64 bits, so if both a1 and b1 are nonzero, we have an overflow right there and can abort.

For the second and third part we do the 32x32->64 multiplication we just used to check for overflow for 32-bit numbers.
This is shifted by 32 bits, so we have an overflow if the upper half of it is nonzero.
Since we already know that either a1 or b1 is zero, we can simply calculate

  a=(uint64_t)(a1)*b0+(uint64_t)(a0)*b1;

At least one half of this term will be zero, so we can't have an overflow in the addition.
Then, if a > 0xffffffff, we have an overflow in the multiplication and can abort.

If we got this far, the result is

  (a << 32) + (uint64_t)(a0)*b0;
We still need to check for overflow in this addition (thanks to Tomi Jylhä-Ollila for pointing this out).
Then we can return the result.
*/

#include "../standardHeaders.h"

typedef struct big64
{
	uint32_t v[2]; /* num = v[0] + (v[1] << 32)  - "little endian" */
}big64_t;

// typedef struct big64 big64_t;

typedef struct big128
{
	uint32_t v[4];
}big128_t;

// typedef struct big128 big128_t;

big128_t big128_mul(big64_t x, big64_t y)
{

    /*
        z0 = x0 * y0    ==> yields z0_LB and z0_UB
        z1 = x0 * y1    ==> yields z1_LB and z1_UB
        z2 = x1 * y0    ==> yields z2_LB and z2_UB
        z3 = x1 * y1    ==> yields z3_LB and z3_UB

        z4 = z0_UB + Z1_LB + Z2_LB ==> yields z4_LB and z4_UB
        z5 = z4_UB + Z1_UB + Z2_UB ==> yields z5_LB and z5_UB
        
        z6_LB = z3_LB + z5_LB
        z6_UB = z3_UB + z5_UB

        ans = (z6_UB << 96) + (z6_LB << 64) + (z4_LB << 32) + z0_LB

    */
	uint64_t x0 =  x.v[0], x1 = x.v[1];
    uint64_t y0 =  y.v[0], y1 = y.v[1];

    // z0_LB will be your lowest nibble of 32 bits of 128 bit answer
    // i.e. 0-31 bits
	uint64_t z0 = x0 * y0;
    uint32_t z0_LB = z0 & UINT32_MAX;
    uint32_t z0_UB = z0 >> 32u;

	uint64_t z1 = x0 * y1;
    uint32_t z1_LB = z1 & UINT32_MAX;
    uint32_t z1_UB = z1 >> 32u;

	uint64_t z2 = x1 * y0;
    uint32_t z2_LB = z2 & UINT32_MAX;
    uint32_t z2_UB = z2 >> 32u;
	
    uint64_t z3 = x1 * y1;
    uint32_t z3_LB = z3 & UINT32_MAX;
    uint32_t z3_UB = z3 >> 32u;

    // z4_LB will be your second nibble of 32 bits of 128 bit answer
    // i.e. 32-63 bits
    uint64_t z4 = z0_UB + z1_LB + z2_LB;
    uint32_t z4_LB = z4 & UINT32_MAX;
    uint32_t z4_UB = z4 >> 32u;

    uint64_t z5 = z4_UB + z1_UB + z2_UB;
    uint32_t z5_LB = z5 & UINT32_MAX;
    uint32_t z5_UB = z5 >> 32u;

    // z6_LB will be your third nibble of 32 bits of 128 bit answer
    // i.e. 64-95 bits
    z3 += z5;
    uint64_t z6_LB = z3_LB + z5_LB;

    // z6_UB will be your last nibble of 32 bits of 128 bit answer
    // i.e. 96-127 bits
    uint64_t z6_UB = z3_UB + z5_UB;

	big128_t p = {{ z0_LB, z4_LB, z6_LB, z6_UB }};
	return p;
}

int main()
{
	srand(0);
	for (unsigned i = 0; i < 100000000; ++i)
	{
        // create random 64-bit number
		uint64_t a = (uint32_t)rand() | ((uint64_t)((uint32_t)rand()) << 32u);
        
        // create random 64-bit number
		uint64_t b = (uint32_t)rand() | ((uint64_t)((uint32_t)rand()) << 32u);
		
        // split number into two 32 bit numbers for manipulation
        big64_t a_ = {{ a & UINT32_MAX, a >> 32u }};

        // split number into two 32 bit numbers for manipulation
		big64_t b_ = {{ b & UINT32_MAX, b >> 32u }};

        // perform manual multiplication
		big128_t p_ = big128_mul(a_, b_);

        // calculate using normal 64 bit multiplication
		__uint128_t p = (__uint128_t)a * (__uint128_t)b;

        // split it into 4 variables and cross check against our manual calculation
        // performed in big128_mul() function
        uint32_t p1 = (p & UINT32_MAX);
        u_int32_t p2 = ((p >> 32u) & UINT32_MAX);
        u_int32_t p3 = ((p >> 64u) & UINT32_MAX);
        u_int32_t p4 = ((p >> 96u) & UINT32_MAX);

        // assert if multiplications doesn't match
        assert(p_.v[0] == p1);
		assert(p_.v[1] == p2);
		assert(p_.v[2] == p3);
		assert(p_.v[3] == p4);
	}
	return 0;
}
