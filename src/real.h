/*
	RealLib - Library for real number algebra

	Written in 2014 by Mazzuca, Nicole <npmazzuca@gmail.com>

	To the extent possible under law, the author has dedicated all
	copyright and related and neighboring rights to this software
	to the public domain worldwide. This software is distributed
	without any warranty.

	You should have received a copy of the CC0 Public Domain
	Dedication along with this software. If not, see
	<http://creativecommons.org/publicdomain/zero/1.0/>
*/

#ifndef _REAL_H
#define _REAL_H

#include "frac.h"

typedef struct {
	frac   xct;
	double apx;
	bool   exact;
} real;

real   rnew(int num, int den);

real   i2r(int i);
char*  r2s(real r);

real   rsimp(real r);

bool   req(real r1, real r2);
bool   rneq(real r1, real r2);
bool   rmor(real r1, real r2);
bool   rles(real r1, real r2);
bool   reqm(real r1, real r2);
bool   reql(real r1, real r2);

real   radd(real r1, real r2);
real   rsub(real r1, real r2);
real   rmul(real r1, real r2);
real   rdiv(real r1, real r2);
real   rpow(real r1, real r2);

#endif
