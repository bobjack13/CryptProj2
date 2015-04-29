// xor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <math.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

const unsigned int NUM = 8;

void createRand(unsigned *&);
void print(const unsigned *);
unsigned *XOR(unsigned *arr1, unsigned * arr2);


int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));
	unsigned short a = 1;
	unsigned short b = 1;
	unsigned short c = (a^b);

	cout << "Answer = "  << c << endl;//(a ^ b)<<  endl << endl;

	unsigned int *r;
	unsigned int *k;
	unsigned int *t;
	unsigned int *s;
	unsigned int *u;
	unsigned int *w;
	unsigned int *bFinal;
	//unsigned int *myR;
	unsigned int *myRemp;
	unsigned int *myT;
	unsigned int *myTemp;

	createRand(k);
	createRand(r);
	cout << "K = ";
	print(k);
	cout << "R = ";
	print(r);
	s = XOR(k, r);
	cout << "S = ";
	print(s);
	createRand(t);
	cout << "T = ";
	print(t);
	u = XOR(s, t);
	cout << "U = ";
	print(u);
	myTemp = XOR(u, r);
	cout << "m = ";
	print(myTemp);
	myT = XOR(myTemp, k);
	cout << "t = ";
	print(myT);
	w = XOR(u, r);
	cout << "W = ";
	print(w);

	bFinal = XOR(w, t);
	myRemp = XOR(bFinal, s);
	cout << "F = ";
	print(bFinal);
	cout << "r = ";
	print(myRemp);

	return 0;
}

void createRand(unsigned *&arr)
{
	unsigned *temp = new unsigned int [NUM];

	for(unsigned int i = 0; i < NUM; ++i)
	{
		temp[i] = rand() % 2;
	}
	arr = temp;
}

void print(const unsigned *arr)
{
	for(unsigned int i = 0; i < NUM; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

unsigned *XOR(unsigned *arr1, unsigned * arr2)
{
	unsigned *temp = new unsigned int[NUM];

	for(unsigned int i = 0; i < NUM; ++i)
	{
		if(arr1[i] ==arr2[i])
			temp[i] = 0;
		else
			temp[i] = 1;
	}
	return temp;
}

