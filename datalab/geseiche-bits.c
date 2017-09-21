//Grace Seiche - geseiche
/* 
 * CS:APP Data Lab 
 * 
 * <Grace Seiche geseiche>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
	//uses the constant 1010 (0xaa) and bitshifting to create the constant 0xaaaaaaaa
	//used the idea of concatenation
	return ((((((0xaa<<8)+0xaa)<<8)+0xaa)<<8)+0xaa);
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
	//used the overflow to conclude that Tmin = -Tmin (Tmin equals negative Tmin)
	int neg_x = ~x + 1;
	//only exception is that 0 = -0, so must confirm that x != 0
	int not_zero = !(!x);
	int equals_own_negative = !(neg_x ^ x);	  
	return not_zero & equals_own_negative;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	int both_on_bits = x & y; // produces a mask of all bit on in both x and y
	int both_off_bits = ~x & ~y; // produces a mask of all bits off in both x and y
 	return ~both_on_bits & ~both_off_bits; // returns the bits that are not matching
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	int is_not_zero = ~(!(!x))+1;//if x is 0 returns 0x00000000, else returns 0xffffffff
	//takes advantage of a_number & 0 = 0, while a_number & 0xffffffff = a_number
	int new_y = y & is_not_zero;
	int new_z = z & ~is_not_zero;	
	return new_y + new_z;//returns 0 + the correct answer
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
	int x_is_zero = ~(!(x ^ 0)) +1; // produces 0xffffffff if x is zero
	int x_is_neg = x>>31; // determines the sign of x

	//creates a mask with zeros until the leading one and all ones after the leading one
	x = x | (x>>1);
	x = x | (x>>2);
	x = x | (x>>4);
	x = x | (x>>8);
	x = x | (x>>16);

	//shifts over the bits and adds one, to put a one in the greatest bit position
	//and zero in all other bits
	//for both zero and negative numbers, does NOT add a one because zero has no ones to be
	//shifted, so adding a one would return one; and negatives are all ones, so adding zero
	//would overflow into a zero
	x = (x >> 1) + (~x_is_zero & ~x_is_neg & 1);

	// for negatives, returns 0x80000000, else the calculated mask
	// because the calculated mask for a negative is 0xFFFFFFFF, which is not a mask
  return (x_is_neg & x<<31) + (~x_is_neg & x); 
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	int x_less_than_zero = x>>31; //determine positive/negative x
	// to deal with rounding errors, created an adjusted x for both the negative and
	// positive cases
	int neg_val = (x+(1<<n) + (~1+1)) & x_less_than_zero;
	int non_neg_val = x & ~x_less_than_zero;
	//take advantage of adding zero and the desired value
	int correct_value = neg_val + non_neg_val;	
	//shift the adjusted value to divide by 2^n
	return correct_value >> n;
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
	//used bit shifting to grab the sign bit and return 0 for false and 1 for true
  return !(x>>31);
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
	//isolate the leading two bits to use to determine underflow/overflow
	int leading = (x>>30) & 3;
	//if leading 2 bits are same, sign will not change, no error
	int no_flow = ~((!(leading ^ 0)) | (!(leading ^ 3))) +1;
	//if goes from positive to negative, overflow occurs
	int overflow = ~(!(leading ^ 1)) +1;
	//if goes from negative to positive, underflow occurs
	int underflow = ~(!(leading ^ 2))+1;
	// overflow saturates to Tmax and underflow saturates to Tmin
	return (no_flow & x<<1) + (overflow & ~(1<<31)) + (underflow & leading<<30);
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
	int neg_y = ~y + 1;// finds the negative y
	int not_same_sign = (x^y)>>31; // determines whether signs match
	int is_x_neg = !(!(x>>31)); //determines whether x is negative

	//if there are different signs, and x is the negative one, x is less so true
	//else compute x-y (or x + negative_y) and if that is negative then true
	return (not_same_sign & is_x_neg) + (~not_same_sign & (!(!((x + neg_y)>>31))));
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	//split the int into two portions
	int small_dig = x & 15;
	int large_dig = x >> 4;
	//check if 0 <= small digit <= 9
	int neg_small_dig = ~small_dig +1;
	int small_dig_match = !((9 + neg_small_dig)>>31);
	//check if large digit is equal to 3
	int large_dig_match = !(large_dig^3);
	//makes sure both portions match the expected
	return small_dig_match & large_dig_match;
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x){
	// divides the number by four
	int large_init = x>>2;
	// multiplies the number by three
	int large = ((large_init<<1) + large_init);
	// looks at the remainder
	int leftover_init = (x & 3);
	// multiplies the remainder by 3 THEN divides by 4
	int leftover = ((leftover_init<<1) + leftover_init)>>2;
	// determines the sign of x
	int neg = x>>31;
	// checks if the remainder yeilded something other than zero to be added to number
	int div_by_four = !(leftover_init^0);
	// checks whether the number is negative AND there is remainder to be added
	int neg_and_not_div = (neg + div_by_four)>>1;
	// adds the large number, the remainder (fractional) piece, and adjusts for rounding
	return (large + leftover + (neg_and_not_div & 1) + (~neg_and_not_div & 0));
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int log;
	int shift_equal_zero;

	//similar to in greatestBit, creates a mask to find the greatest bit position
	x = x | (x>>1);
	x = x | (x>>2);
	x = x | (x>>4);
	x = x | (x>>8);
	x = x | (x>>16);
	x = (x >> 1) + 1;
	
	//uses a binomial search to find how many zeros(shifts) are before the greatest bit
	log = 0;
	shift_equal_zero = ~(!((x>>16)^0)) +1;
	log = log + (~shift_equal_zero & 16);
	shift_equal_zero = ~(!((x>>(log + 8))^0)) +1;
	log = log + (~shift_equal_zero & 8);
	shift_equal_zero = ~(!((x>>(log + 4))^0)) +1;
	log = log + (~shift_equal_zero & 4);
	shift_equal_zero = ~(!((x>>(log + 2))^0)) +1;
	log = log + (~shift_equal_zero & 2);
	shift_equal_zero = ~(!((x>>(log + 1))^0)) +1;
	log = log + (~shift_equal_zero & 1);

	// the number of shifts/zeros is the log
  return log;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	// isolates the exponent and the mantissa
	int man = uf & 0x7FFFFF;
	// is exponent not a number
	int isExpNan = (uf >> 23) & 0xFF;
	// if the exponent is 255 and the mantissa in not zero, it is not a number
	// and must return itself
	if((isExpNan == 255) && (man != 0)){
		return uf;}
	else{// otherwise, isolate the sign bit
		return uf^0x80000000;}
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	//pre-declaration of variables
	int exp;
	//int man_count;
	//int man;
	int man_mask;
	int exp_mask;
	int copy_abs_x;
	int abs_x;
	int sign_mask;
	int bias_exp;

	//printf("x is %x\n", x);

	// odd cases, 0 and Tmin
	if (x == 0){
		return 0;
	}
	if (x == 0x80000000){
		return 0xcf000000;
	}

	//sign
	sign_mask = x & 0x80000000;

	//create absolute values
	abs_x = x;
	if (abs_x <0){
		abs_x = (~abs_x +1);
	}
	//printf("%x\n", abs_x);
	copy_abs_x = abs_x;

	//exponent
	exp = 0;
	//printf ("%x\n", abs_x);
///*
	//counts the bits to the right of the leading one for the exponent
	while ((abs_x >> 1) != 0){
		abs_x = abs_x >> 1;
		//printf("%x\n", abs_x); 
		exp++;
		//printf("loop\n");
	}
//*/
	//printf("check\n");

	//calculates the biased exponent
	bias_exp = exp;
	if(x != 0){
		bias_exp = exp + 127;
	}

	//writes the mask for the exponent bits
	exp_mask = (bias_exp << 23) & 0x7F800000;
	//printf ("%x\n", exp);

//PLEASE NOTE: From what I have seen, my code is correct up to this point. The first nine bits
// of my answers match the first nine bits of the correct answer. 
// Where I struggled and ran out of time was the mantissa. I was unable to successfully figure
// out an algorithm for the mantissa and I wish I had more time to keep trying. Fundamentally, 
// I am struggling to calculate the mantissa of an integer. I have tried multiple approaches, 
// (some are commented out, but left for you to see). I looked online for examples of how to 
// manually calculate the mantissa and asked my fellow students general questions about 
// how they approached the mantissa, but in the end it did not work out, which is especially 
// disappointing to me. After this project ends, I want to look at what other students did, so
// I can figure out the mantissa on my own. Unfortunately though, I was not able to complete 
// this task during the alotted time frame.

	// complete i2f - attempt 1
/*
	//printf("number: %x\n", x);

	if (x ==0) { return 0; }
	if (x ==0x80000000) { return 0xcf000000; }

	int sign = x & 0x80000000;

	int abs_x = x;
	if(x<0){
		abs_x = ~x+1;
	}
	
	int shifts = 0;
	int shifted_val = abs_x;
	while (shifted_val > 0){
		shifted_val = shifted_val >> 1;
		shifts++;
	}
	//printf("shifts: %d\n", shifts);
	int exp = (127 + shifts) << 23;
	int man = (abs_x & ~(0x80000000 >> (32 - shifts)))>>8;
	
	//printf("sign: %x\texp: %x\tman: %x\n", sign, exp, man);

	unsigned result = (sign ^ exp) ^ man;
	
	return result;
*/

	//mantissa - attempt 2
/*
	man_count = 22;
	man_mask = 0;
	man = copy_abs_x / (copy_abs_x - (1 << (exp+1)));
	printf("%x\n", man);
	while (man_count > 0){
		if(man > (1<<man_count)){
			man = man - (1 << man_count);
			man_mask = man_mask + (1 << (22 - man_count));
		}
		man_count--;
	}
*/

	// mantissa - attempt 3
	man_mask = (copy_abs_x << (23 - exp)) & 0x007FFFFF;

	// combines all the masks into one mask
	return sign_mask ^ exp_mask ^ man_mask;
	
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {

	// if uf is zero or Tmin return itself
	if(uf==0 || uf==0x80000000){
		return uf;
	} else if ((uf & 0x7f800000)==0){ //if the exponent is 0
		int man = (uf & 0x007FFFFF)<<1; // double the mantissa
		return (uf & 0xFF800000) + man; // return the same sign and exp with new man
	} else if((uf & 0x7f800000)==0x7f800000){// if exponent is 255, return itself
		return uf;
	} else {
		return uf + 0x00800000;// otherwise, increase the exponent by one
	}
}
