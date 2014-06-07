/*
	SciCalcRPN - A Scientific Calculator

	Copyright (c) 2014, Nicole Mazzuca <nicole@strega-nil.co>
	
	All rights reserved.

	Redistribution and use in source and binary forms, with or without 
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice, 
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "stack.h"
#include <stdio.h>

#define STACKSIZE 50

real stack[STACKSIZE];
int   curstksize = 0;

int StackPush(real r)
{
	if(curstksize == STACKSIZE){
		curstksize = STACKSIZE - 1;
	}
	for(int i = curstksize; i > 0; --i){
		stack[i] = stack[i - 1];
	}

	stack[0] = r;

	++curstksize;
	return 0;
}

int StackDel(void)
{
	if(curstksize == 0){
		return 1;
	}
	for(int i = 0; i < curstksize; ++i){
		stack[i] = stack[i + 1];
	}

	--curstksize;
	return 0;
}

int StackPrint(void)
{
	if(curstksize < 1){
		return 0;
	}

	for(int i = curstksize - 1; i >= 0; --i){
		printf("%s\n", r2s(stack[i]));
	}
	
	return 0;
}

int StackAdd(void)
{
	if(curstksize < 2){
		return 1;
	}

	stack[0] = radd(stack[1], stack[0]);
	for(int i = 1; i < curstksize - 1; ++i){
		stack[i] = stack[i + 1];
	}

	--curstksize;
	return 0;
}

int StackSub(void)
{
	if(curstksize < 2){
		return 1;
	}

	stack[0] = rsub(stack[1], stack[0]);
	for(int i = 1; i < curstksize - 1; ++i){
		stack[i] = stack[i + 1];
	}

	--curstksize;
	return 0;
}

int StackMul(void)
{
	if(curstksize < 2){
		return 1;
	}

	stack[0] = rmul(stack[1], stack[0]);
	for(int i = 1; i < curstksize - 1; ++i){
		stack[i] = stack[i + 1];
	}

	--curstksize;
	return 0;
}

int StackDiv(void)
{
	if(curstksize < 2){
		return 1;
	}

	stack[0] = rdiv(stack[1], stack[0]);
	for(int i = 1; i < curstksize - 1; ++i){
		stack[i] = stack[i + 1];
	}

	--curstksize;
	return 0;
}

int StackPow(void)
{
	if(curstksize < 2){
		return 1;
	}

	stack[0] = rpow(stack[1], stack[0]);
	for(int i = 1; i < curstksize - 1; ++i){
		stack[i] = stack[i + 1];
	}

	--curstksize;
	return 0;
}
