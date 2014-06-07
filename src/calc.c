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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUTSIZE 19

frac s2f(char*);
int  getInput(char*);

int main(void)
{
	char input[INPUTSIZE];
	while(true){
		printf(" ");
		getInput(input);
		if(input[0] == '+' && input[1] == '\0'){
			if(StackAdd()){
				fprintf(stderr, "Error: Not Enough Arguments\n");
			}
		} else if(input[0] == '-' && input[1] == '\0'){
			if(StackSub()){
				fprintf(stderr, "Error: Not Enough Arguments\n");
			}
		} else if(input[0] == '*' && input[1] == '\0'){
			if(StackMul()){
				fprintf(stderr, "Error: Not Enough Arguments\n");
			}
		} else if(input[0] == '/' && input[1] == '\0'){
			if(StackDiv()){
				fprintf(stderr, "Error: Not Enough Arguments\n");
			}
		} else if(input[0] == '^' && input[1] == '\0'){
			if(StackPow()){
				fprintf(stderr, "Error: Not Enough Arguments\n");
			}
		} else if((input[0] >= '0' && input[0] <= '9') || ((input[0] == '-' || input[0] == '+') && (input[1] >= '0' && input[1] <= '9'))){

			bool fraction = true;
			real r;
			frac xct;
			for(int i = 0; input[i] != '\0'; i++){
				if(input[i] == '.'){
					fraction = false;
					break;
				}
			}
			
			if(fraction){
				xct = s2f(input);
				r.xct = xct;
				r.apx = f2d(xct);
				r.exact = true;
			} else {
				r.xct = fnew(1,0);
				r.apx = atof(input);
				r.exact = false;
			}

			StackPush(r);

		} else if(!strcmp(input, "del") || !strcmp(input, "d")){
			if(StackDel()){
				fprintf(stderr, "Error: No Stacked Numbers to Delete\n");
			}
		} else if(!strcmp(input, "exit") || !strcmp(input, "quit")){
			return 0;
		} else {
			fprintf(stderr, "Error: Unrecognized Command\n");
		}
		StackPrint();
	}
	return 0;
}

frac s2f(char* str)
{
	char numstr[INPUTSIZE];
	int slash, num, den;
	for(int i = 0; (str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '+'; i++){
		numstr[i] = str[i];
		slash = i + 1;
	}
	sscanf(numstr, "%i", &num);

	if(str[slash] == '/'){
		++slash;
		for(int i = 0; (str[i] >= '0' && str[i] <= '9'); i++){
			numstr[i] = str[i + slash];
		}
		sscanf(numstr, "%i", &den);
	} else {
		den = 1;
	}

	return fnew(num, den);
}

int getInput(char* str)
{
	char c;
	for(int i = 0; i < INPUTSIZE; i++){
		c = getchar();
		if(c == '\n' || i == INPUTSIZE - 1){
			str[i] = '\0';
			break;
		} else {
			str[i] = c;
		}
	}

	while(c != '\n'){
		c = getchar();
	}

	return 0;
}
