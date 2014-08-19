#include <iostream>
#include <conio.h>

using namespace std;

double inline __declspec(naked) __fastcall qsqrt(double n)
{
	_asm fld qword ptr[esp + 4]
	_asm fsqrt
	_asm ret 8
}

int main()
{
	cout << qsqrt(4);
	_getch();
	return 0;
}
