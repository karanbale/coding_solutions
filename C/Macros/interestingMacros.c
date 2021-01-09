#include "../standardHeaders.h"

// Here are the macros to get the minimum and maximum values for a given integer type:

#define __HALF_MAX_SIGNED(type) ((type)1 << (sizeof(type)*8-2))
#define __MAX_SIGNED(type) (__HALF_MAX_SIGNED(type) - 1 + __HALF_MAX_SIGNED(type))
#define __MIN_SIGNED(type) (-1 - __MAX_SIGNED(type))

#define __MIN(type) ((type)-1 < 1?__MIN_SIGNED(type):(type)0)
#define __MAX(type) ((type)~__MIN(type))

// Finding out whether we can assign a value to a variable without truncation

#define assign(dest,src) ({ \
  typeof(src) __x=(src); \
  typeof(dest) __y=__x; \
  (__x==__y && ((__x<1) == (__y<1))?(void)((dest)=__y),0:1); \
})

// add positive numbers:

#define __add_of(c,a,b) ({ \
  typeof(a) __a=a; \
  typeof(b) __b=b; \
  ((__MAX(typeof(c))-(__b) >= (__a))?assign(c,((typeof(c))__a+__b):1); \
})

// Adding and subtracting arbitrary integers
// Now that we have a macro that will work for adding positive integers,
// it's easy to generalize this into a macro that will work for negative integers, too:

#define add_of(c,a,b) ({ \
  typeof(a) __a=a; \
  typeof(b) __b=b; \
  (__b)<1 ? \
    ((__MIN(typeof(c))-(__b)<=(__a))?assign(c,(typeof(c))__a+__b):1) : \
    ((__MAX(typeof(c))-(__b)>=(__a))?assign(c,(typeof(c))__a+__b):1); \
})

// And the subtraction macro works just the same:

#define sub_of(c,a,b) ({ \
  typeof(a) __a=a; \
  typeof(b) __b=b; \
  (__b)<1 ? \
    ((__MAX(typeof(c))+(__b)>=(__a))?assign(c,(typeof(c))__a-__b):1) : \
    ((__MIN(typeof(c))+(__b)<=(__a))?assign(c,(typeof(c))__a-__b):1); \
})

// a routine that can multiply two 32-bit numbers, returning a 32-bit number, and checking for overflow:

int umult32(uint32_t a,uint32_t b,uint32_t *c) {
  unsigned long long x=(unsigned long long)a*b;
  if (x>0xffffffff) return 0;
  *c=x&0xffffffff;
  return 1;
}

/*
Multiplying 16-bit values with overflow check works the same way. 
Note that it is:

  (unsigned long long)a*b

and not

  (unsigned long long)(a*b)

which is a typical mistake of inexperienced C hackers.
In the second case, the result is first truncated, and then cast to 64-bit,
zeroing the upper bits, and the code will never detect an overflow.
*/


/*
Using __auto_type instead of typeof has two advantages:

Each argument to the macro appears only once in the expansion of the macro.
This prevents the size of the macro expansion growing exponentially when calls to such macros are nested inside arguments of such macros.
If the argument to the macro has variably modified type, it is evaluated only once when using __auto_type, but twice if typeof is used.
*/
#define max(a,b) \
  ({ __auto_type _a = (a); \
      __auto_type _b = (b); \
    _a > _b ? _a : _b; })
