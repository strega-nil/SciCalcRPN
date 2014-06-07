/*
	Prime Generator - Part of the SciCalcRPN Project

	Written in 2014 by Kruper, John.
	Edited for this project by Mazzuca, Nicole <nicole@strega-nil.co>.

	To the extent possible under law, the author has dedicated all
	copyright and related and neighboring rights to this software
	to the public domain worldwide. This software is distributed
	without any warranty.

	You should have received a copy of the CC0 Public Domain
	Dedication along with this software. If not, see
	<http://creativecommons.org/publicdomain/zero/1.0/>
*/

#include <stdio.h>
#include <stdbool.h>

#define NMax 100

int main(void)
{
	int length = 1;
	bool prime = true;

	printf("#ifndef PRIMES_H\n");
	printf("#define PRIMES_H\n\n");
	printf("const int PRIMES[] = {2");

	for (int i = 3; length < NMax && i < 1000; i++){
		for(int j = i - 1; j > 1; j--){
			if (i % j == 0){
				prime = false;
			}
		}
		if (prime){
			printf(", %d", i);
			length++;
		}

		prime = true;
	}

	printf("};\n");
	printf("const int PRIMESLENGTH = %d;\n\n", NMax);
	printf("#endif\n");

	return 0;
}
