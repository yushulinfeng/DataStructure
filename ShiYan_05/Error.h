#include "stdafx.h"
#include <iostream>
using namespace std;

/* �쳣  �ඨ��*/
class OutOfBounds
{
public:
	OutOfBounds() { cout << "OutOfBounds!!!" << endl; }
};

class MustBeZero
{
public:
	MustBeZero() { cout << "MustBeZero!!!" << endl; }
};

class NOMEM
{
public:
	NOMEM() { cout << "NOMEM!!!" << endl; }
};

class SizeMismatch
{
public:
	SizeMismatch() { cout << "SizeMismatch!!!" << endl; }
};

class BadInitializers
{
public:
	BadInitializers() { cout << "BadInitializers!!!" << endl; }
};

class BadInput
{
public:
	BadInput() { cout << "BadInput!!!" << endl; }
};
