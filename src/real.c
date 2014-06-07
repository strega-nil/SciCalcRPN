/*
	RealLib - Library for real number algebra

	Written in 2014 by Mazzuca, Nicole <nicole@strega-nil.co>

	To the extent possible under law, the author has dedicated all
	copyright and related and neighboring rights to this software
	to the public domain worldwide. This software is distributed
	without any warranty.

	You should have received a copy of the CC0 Public Domain
	Dedication along with this software. If not, see
	<http://creativecommons.org/publicdomain/zero/1.0/>
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "real.h"


/** INTERNAL: Changes two fraction dens to the same int.
 *
 *  Takes two fraction pointers, f1 and f2, and changes the
 *  denominators to equal each other, by multiplying the
 *  num/den by the opposite denominator.
 */
int rlcf(real* r1, real* r2)
{
	if(r1->xct.den == r2->xct.den){
		return 0;
	}
	
	int d1 = r1->xct.den;
	int d2 = r2->xct.den;

	r1->xct.num = r1->xct.num * d2;
	r1->xct.den = r1->xct.den * d2;

	r2->xct.num = r2->xct.num * d1;
	r2->xct.den = r2->xct.den * d1;
	
	return 0;
}

/** Takes fracs base and exp, returns real base^exp.
 *  This is the best way to make a real number for use
 *  with this library.
 *  Remember fnew(num, den) in order to create fracs.
 */
real rnew(int num, int den)
{
	real r = {fnew(num,den), (double)num / den, true};
	return r;
}

// Fraction Casters

/** Takes an int n, returns fraction n/1.
 *  Exactly what it sounds like on the tin
 *  (int to real).
 */
real i2r(int n)
{
	return rnew(n, 1);
}

/** Takes a real r, returns a string, for printing &c.
 *  If the root is 1, then it returns a string that looks like
 *  a fraction. Otherwise, it returns "f^d".
 *  Uses f2s, from the frac library.
 *  If the denominator of either f or d = 1, that part looks like an int.
 *  Otherwise, that part looks like "num/den".
 */
char* r2s(real r)
{
	char* str;
	if(!r.exact){
		str = malloc(3 + DBL_MANT_DIG - DBL_MIN_EXP);
		sprintf(str, "%+G", r.apx);
		return str;
	}
	return f2s(r.xct);
}

// Real Number Boolean Operators

/** f1 == f2 
 */

bool req(real r1, real r2)
{
	if(!r1.exact || !r2.exact){
		return (r1.apx == r2.apx);
	}

	rlcf(&r1, &r2);
	if(r1.xct.num == r2.xct.num){
		return true;
	} else {
		return false;
	}
}

/** f1 != f2
 */
bool rneq(real r1, real r2)
{
	return !(req(r1, r2));
}

/** f1 > f2
 */
bool rmor(real r1, real r2)
{
	if(!r1.exact || !r2.exact){
		return (r1.apx > r2.apx);
	}
	
	rlcf(&r1, &r2);

	if(r1.xct.num > r2.xct.num){
		return true;
	} else {
		return false;
	}
}

/** f1 < f2
 */
bool rles(real r1, real r2)
{
	return rmor(r2, r1);
}

/** f1 >= f2
 */
bool reqm(real r1, real r2)
{
	return !(rmor(r2, r1));
}

/** f1 <= f2
 */
bool reql(real r1, real r2)
{
	return !(rmor(r1, r2));
}


// Fraction Arithmetic

/** f1 + f2.
 *  First changes the denominators of f1 and f2
 *  to be equal, then adds the numerators, and finally
 *  returns the answer.
 */
real radd(real r1, real r2)
{
	if(!r1.exact || !r2.exact){
		r1.apx = r1.apx + r2.apx;
		r1.exact = false;
		return r1;
	}

	rlcf(&r1, &r2);

	r1.xct.num = r1.xct.num + r2.xct.num;

	r1.apx = f2d(r1.xct);

	return r1;
}

/** f1 - f2.
 *  First changes the denominators of f1 and f2
 *  to be equal, then subtracts the numerators, and finally
 *  returns the answer.
 */
real rsub(real r1, real r2)
{
	if(!r1.exact || !r2.exact){
		r1.apx = r1.apx - r2.apx;
		r1.exact = false;
		return r1;
	}

	rlcf(&r1, &r2);

	r1.xct.num = r1.xct.num - r2.xct.num;

	r1.apx = f2d(r1.xct);

	return r1;
}

/** f1 * f2.
 *  Multiplies the numerators, multiplies the denominators,
 *  and returns the product.
 */
real rmul(real r1, real r2)
{
	r1.xct.num = r1.xct.num * r2.xct.num;
	r1.xct.den = r1.xct.den * r2.xct.den;

	fsimp(r1.xct);

	r1.apx = f2d(r1.xct);

	return r1;
}

/** f1 / f2.
 *  Multiplies f1 by the reciprocal of f2.
 *  So it multiplies f1.num by f2.den, and vice versa, then
 *  returns the product.
 */
real rdiv(real r1, real r2)
{
	r1.xct.num = r1.xct.num * r2.xct.den;
	r1.xct.den = r1.xct.den * r2.xct.num;

	fsimp(r1.xct);

	r1.apx = f2d(r1.xct);

	return r1;
}

/** f1 ^ f2.
 *  Exponentiates f1 by f2, so you multiply f1 by itself f2.num
 *  times. Then, you root f1 by f2.den.
 */
real rpow(real r1, real r2)
{
	if(r1.exact && r2.exact && r2.xct.den == 1){
		r1.xct = fpow(r1.xct, r2.xct.num);
	}

	r1.exact = false;

	r1.apx = pow(r1.apx, r2.apx);

	return r1;
}
