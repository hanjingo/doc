English | [中文版](eight_queen_zh.md)

# Eight Queens Problem

[TOC]



Problem: Use the digits 1-9 to form three numbers abc, def, ghi such that abc:def:ghi = 1:2:3.

167-character answer:
```c++
g(x,y,z){x*2==y&x*3==z&&printf("%d,%d,%d\n",x,y,z);}
f(i,j,m,r){i?1<<j&m||f(i-1,1,m|1<<j,r*10+j),j<10&&f(i,j+1,m,r):g(r/1000000,r/1000%1000,r%1000);}
main(){
	f(9,1,0,0);
}
```
Compile and output:
```sh
gcc -w a.c && ./a.out
192,384,576
219,438,657
273,546,819
327,654,981
```
Clearly, there are nine nested loops.

## Update 1: How to Express n-level for Loops with Recursion
In "Milo Yip: What Problems Can Two for Loops Solve?", I mentioned:

Two nested for loops can generate the Cartesian product A × B for two sets A, B; to do nine nested for loops for set A = {1, 2, 3, ..., 9}, it can be expressed as \underbrace{ A \times A \times \cdots \times A}_9 = A^9 .

Suppose we write 9 for loops directly:
```c++
#include <stdio.h>

void output(const int* a) {
	for (int i = 0; i < 9; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main() {
	int a[9];

	for (a[8] = 1; a[8] < 10; a[8]++)
	 for (a[7] = 1; a[7] < 10; a[7]++)
	  for (a[6] = 1; a[6] < 10; a[6]++)
	   for (a[5] = 1; a[5] < 10; a[5]++)
		for (a[4] = 1; a[4] < 10; a[4]++)
		 for (a[3] = 1; a[3] < 10; a[3]++)
		  for (a[2] = 1; a[2] < 10; a[2]++)
		   for (a[1] = 1; a[1] < 10; a[1]++)
			for (a[0] = 1; a[0] < 10; a[0]++)
				output(a);
}
```
Output:
```sh
1 1 1 1 1 1 1 1 1 
2 1 1 1 1 1 1 1 1 
3 1 1 1 1 1 1 1 1 
...
1 2 1 1 1 1 1 1 1
2 2 1 1 1 1 1 1 1
3 2 1 1 1 1 1 1 1
...
9 9 9 9 9 9 9 9 9
```
But we can consider: A^n = A × A^{n - 1}

We can use this recursive form, defining a function that only does one for loop to represent one Cartesian product in the above formula:
```c++
#include <stdio.h>

void output(const int* a) {
	for (int i = 0; i < 9; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void f(int* a, int n) {
	for (a[n] = 1; a[n] < 10; a[n]++)
		if (n == 0)
			output(a);
		else
			f(a, n - 1);
}

int main() {
	int a[9];
	f(a, 8);
}
```
This is a general way to write n for loops recursively. If n is not a constant, recursion is a simple solution. Back to the original problem, it actually only needs permutations of A, i.e., 9! = 362880 tests. The original answer used combinations and a bit set to avoid duplicate digits, but the ideal approach is to directly generate all permutations [1].

## Update 2: "Decompressed" Version of the Original Answer:
```c++
#include <stdio.h>

void outputIfValid(int abc, int def, int ghi) {
	if (abc * 2 == def && abc * 3 == ghi)
		printf("%d,%d,%d\n", abc, def, ghi);
}

// The i-th for loop, m is a bit set representing used digits, r is the current permutation abcdefghi
void f(int i, int m, int r) {
	if (i == 0)
		outputIfValid(r / 1000000, r / 1000 % 1000, r % 1000); // abcdefghi -> abc, def, ghi
	else
		for (int j = 1; j < 10; j++)
			if (((1 << j) & m) == 0)                 // if j has not been used
				f(i - 1, m | (1 << j), r * 10 + j);  // add j to m and r, enter i - 1 loop
}

int main() {
	f(9, 1, 0);
}
```

## Update 3: C++03 Version Using std::next_permutation
```c++
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

int main() {
	int a[9];
	iota(a, a + 9, 1);
	do {
		int abc = a[0] * 100 + a[1] * 10 + a[2];
		int def = a[3] * 100 + a[4] * 10 + a[5];
		int ghi = a[6] * 100 + a[7] * 10 + a[8];
		if (abc * 2 == def && abc * 3 == ghi)
			cout << abc << "," << def << "," << ghi << endl;
	} while(next_permutation(a, a + 9));
}
```
